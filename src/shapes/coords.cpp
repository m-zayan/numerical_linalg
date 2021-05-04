/*
 * coords.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./coords.hpp"

coords::coords() :
		shape( { }), ndim(0), size1d(0), strides( { }), axes( { }), order('C'), own_data(
				1) {

}

coords::coords(shape_t shape) :
		shape(shape), ndim(shape.size()), size1d(
				shape.multiply(0, shape.size())), strides(
				this->get_strides(shape)), axes( { }), order('C'), own_data(1) {

	this->axes.range(0, shape.size(), 1);
}

coords::coords(shape_t shape, char order) :
		coords::coords(shape) {

	this->order = order;
}

coords::coords(shape_t shape, bool own_data) :
		coords::coords(shape) {

	this->own_data = own_data;
}

coords::coords(shape_t shape, shape_t strides, bool own_data) {

	this->check_strides(shape, strides);

	this->shape = shape;
	this->strides = strides;
	this->ndim = shape.size();
	this->size1d = shape.multiply(0, shape.size());
	this->order = 'C';
	this->own_data = own_data;

	this->axes.range(0, shape.size(), 1);
}

coords::coords(shape_t shape, shape_t axes, shape_t strides, bool own_data) :
		coords::coords(shape, strides, own_data) {

	this->axes = axes;
}

coords::~coords() {
}

coords::coords(const coords &attr) :
		shape(attr.shape), ndim(attr.ndim), size1d(attr.size1d), strides(
				attr.strides), axes(attr.axes), order(attr.order), own_data(
				attr.own_data) {

}

coords::coords(const coords &&attr) :
		shape(std::move(attr.shape)), ndim(attr.ndim), size1d(attr.size1d), strides(
				std::move(attr.strides)), axes(std::move(attr.axes)), order(
				attr.order), own_data(attr.own_data) {
}

coords& coords::operator =(const coords &attr) {

	this->shape = attr.shape;
	this->strides = attr.strides;
	this->axes = attr.axes;

	this->ndim = attr.ndim;
	this->size1d = attr.size1d;
	this->order = attr.order;
	this->own_data = attr.own_data;

	return (*this);
}

shape_t coords::get_strides(shape_t shape) {

	shape_t strides;

	if (shape.size() > 1) {

		strides.reserve(shape.size());

		for (max_size_t i = 1; i < shape.size() - 1; i++) {

			max_size_t begin = i;
			max_size_t end = ndim - 1;

			strides.push_back(
					shape.multiply(begin, end) * shape[shape.size() - 1]);
		}

		strides.push_back(shape[shape.size() - 1]);
		strides.push_back(1);

	} else {

		strides.push_back(1);
	}

	return strides;
}

void coords::check_strides(shape_t shape, shape_t strides) {

	for (max_size_t i = 0; i < shape.size() - 1; i++) {

		if (strides[i] % shape[i] != 0
				|| (strides[i] / shape[i]) != strides[i + 1]) {

			nd::exception("Invalid coords(shape, strides), shape, "
					"doesn't match with the given strides");
		}
	}
}

coords coords::permuted(const shape_t &axes, bool own_data) const {

	shape_t tmp_shape = this->shape;
	shape_t tmp_strides = this->strides;
	shape_t tmp_axes = axes;

	if (tmp_axes.size() != this->ndim) {

		throw nd::exception(
				"Invalid number of axes, axes.size() != this->ndim()");
	}

	shape_t swaped_shape(this->ndim);
	shape_t swaped_strides(this->ndim);

	for (max_size_t i = 0; i < axes.size(); i++) {

		if (tmp_axes[i] >= this->ndim) {

			throw nd::exception("Invalid axes, axes[i] >= this->ndim()");
		}

		swaped_shape[i] = tmp_shape[tmp_axes[i]];
		swaped_strides[i] = tmp_strides[tmp_axes[i]];
	}

	coords new_attr(swaped_shape, tmp_axes, swaped_strides, own_data);

	return new_attr;
}

coords coords::reverse_permute(bool own_data) const {

	shape_t tmp_axes = this->axes;

	shape_t reaxes(this->ndim);

	for (max_size_t i = 0; i < this->ndim; i++) {

		reaxes[tmp_axes[i]] = i;
	}

	coords new_attr = this->permuted(reaxes, own_data);

	return new_attr;
}

coords coords::swapaxes(max_size_t ax0, max_size_t ax1, bool own_data) const {

	if (ax0 >= this->ndim || ax1 >= this->ndim) {

		throw nd::exception(
				"Invalid axis of axes, ax0 >= this->ndim || ax1 >= this->ndim");
	}

	;
	shape_t swapped_axes = this->axes;

	std::swap(swapped_axes[ax0], swapped_axes[ax1]);

	coords new_attr = this->permuted(swapped_axes, own_data);

	return new_attr;
}

coords coords::reduce(max_size_t axis, bool keepdims) const {

	max_size_t ndim = this->ndim - 1;

	if (keepdims) {
		ndim += 1;
	}

	shape_t in_shape = this->shape;
	shape_t out_shape(ndim);

	max_size_t k = 0;

	for (max_size_t i = 0; i < ndim; i++) {

		if (i == axis) {
			if (keepdims) {
				out_shape[k++] = 1;
			}

			continue;
		}

		out_shape[k++] = in_shape[i];
	}

	coords new_attr = coords(out_shape);

	return new_attr;
}

coords coords::pad_dim(max_size_t new_ndim) const {

	max_size_t ndim = this->ndim;
	max_size_t max_ndim = std::max(new_ndim, ndim);

	max_size_t pad_size = max_ndim - ndim;

	shape_t shape = this->shape;
	shape_t strides = this->strides;
	shape_t axes = this->axes;

	shape_t new_shape(max_ndim, 1);
	shape_t new_strides(max_ndim, strides[0]);
	shape_t new_axes(max_ndim);

	shape_t tmp_axes(max_ndim);

	tmp_axes.range(0, max_ndim, 1);

	for (max_size_t i = 0; i < ndim; i++) {

		new_shape[pad_size + i] = shape[i];
		new_strides[pad_size + i] = strides[i];
	}

	for (max_size_t i = 0; i < ndim; i++) {

		new_axes[pad_size + i] = tmp_axes[pad_size + axes[i]];
	}

	coords new_attr(new_shape, new_axes, new_strides, this->own_data);

	return new_attr;
}

void coords::swapaxes(max_size_t ax0, max_size_t ax1) {

	if (ax0 >= this->ndim || ax1 >= this->ndim) {

		throw nd::exception(
				"Invalid axis of axes, ax0 >= this->ndim || ax1 >= this->ndim");
	}

	std::swap(this->axes[ax0], this->axes[ax1]);
	std::swap(this->shape[ax0], this->shape[ax1]);
	std::swap(this->strides[ax0], this->strides[ax1]);
}

bool operator ==(const coords &attr1, const coords &attr2) {

	coords temp1 = attr1;
	coords temp2 = attr2;

	if (temp1.ndim == temp2.ndim) {
		for (max_size_t i = 0; i < temp1.ndim; i++) {
			if (temp1.shape[i] != temp2.shape[i]) {
				return false;
			}
		}
		return true;
	}

	else {
		return false;
	}
}

// =============================== shape_t ===============================

std::ostream& operator <<(std::ostream &os, shape_t shape) {

	os << '(';

	for (max_size_t i = 0; i < shape.size() - 1; i++) {
		os << shape[i] << ',';
	}

	os << shape[shape.size() - 1];

	if (shape.size() == 1) {
		os << ',';
	}

	os << ')';

	return os;
}

// flags: {0: doesn't match, 1: match, 2: broadcastable}
uflag8_t operator &(const shape_t &shape1, const shape_t &shape2) {

	shape_t temp1 = shape1;
	shape_t temp2 = shape2;

	max_size_t size1 = temp1.size();
	max_size_t size2 = temp2.size();

	uflag8_t flag = 1;

	if (size1 == size2) {
		for (max_size_t i = 0; i < size1; i++) {
			if (temp1[i] != temp2[i]) {

				if (temp1[i] == 1 || temp2[i] == 1) {

					flag = 2;
				}

				else {
					return 0;
				}
			}
		}
		return flag;
	}

	else {

		max_size_t i, j;

		if (size1 > size2) {
			i = size1 - size2;
			j = 0;
		}

		else {
			i = 0;
			j = size2 - size1;
		}

		while (i < size1 && j < size2) {

			if ((temp1[i] != temp2[j]) && !(temp1[i] == 1 || temp2[j] == 1)) {
				return 0;
			}

			i++;
			j++;
		}

		return 2;
	}
}

