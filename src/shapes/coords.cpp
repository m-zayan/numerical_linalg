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

coords coords::reduce(max_size_t axis) {

	shape_t in_shape = this->shape;
	shape_t out_shape(this->ndim - 1);

	max_size_t k = 0;

	for (max_size_t i = 0; i < this->ndim; i++) {

		if (i == axis)
			continue;

		out_shape[k++] = in_shape[i];
	}

	coords new_attr = coords(out_shape);

	return new_attr;
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
