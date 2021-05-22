/*
 * coords.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./coords.hpp"

// =================================================================

bounded_t<max_size_t> nd::mem::AUX_SIZE( { 2, 512, 1028, 2048 }, "AUX_SIZE",
		2048);

bounded_t<uflag8_t> nd::state::BroadcastingLevel( { 0, 1, 2 },
		"BroadcastingLevel", 2);

// =================================================================

coords::coords() :
		shape( { }), ndim(0), size1d(0), strides( { }), axes( { }), order('C'), own_data(
				1), iter_type(IteratorType::None) {

}

coords::coords(shape_t shape) :
		shape(shape), ndim(shape.size()), size1d(coords::get_size1d(shape)), strides(
				coords::get_strides(shape)), axes( { }), order('C'), own_data(
				1), iter_type(IteratorType::None) {

	this->axes.range(0, shape.size(), 1);
}

coords::coords(shape_t shape, char order) :
		coords::coords(shape) {

	this->order = order;
}

coords::coords(shape_t shape, bool own_data, IteratorType iter_type) :
		coords::coords(shape) {

	this->own_data = own_data;
	this->iter_type = iter_type;
}

coords::coords(shape_t shape, shape_t strides, bool own_data,
		IteratorType iter_type) {

	coords::check_strides(shape, strides);

	this->shape = shape;
	this->strides = strides;
	this->ndim = shape.size();
	this->size1d = coords::get_size1d(shape);
	this->order = 'C';
	this->own_data = own_data;

	this->axes.range(0, shape.size(), 1);

	this->iter_type = iter_type;
}

coords::coords(shape_t shape, shape_t axes, shape_t strides, bool own_data,
		IteratorType iter_type) :
		coords::coords(shape, strides, own_data, iter_type) {

	this->axes = axes;
}

coords::~coords() {
}

coords::coords(const coords &attr) :
		shape(attr.shape), ndim(attr.ndim), size1d(attr.size1d), strides(
				attr.strides), axes(attr.axes), order(attr.order), own_data(
				attr.own_data), iter_type(attr.iter_type) {

}

coords::coords(const coords &&attr) :
		shape(std::move(attr.shape)), ndim(attr.ndim), size1d(attr.size1d), strides(
				std::move(attr.strides)), axes(std::move(attr.axes)), order(
				attr.order), own_data(attr.own_data), iter_type(attr.iter_type) {
}

coords& coords::operator =(const coords &attr) {

	this->shape = attr.shape;
	this->strides = attr.strides;
	this->axes = attr.axes;

	this->ndim = attr.ndim;
	this->size1d = attr.size1d;
	this->order = attr.order;
	this->own_data = attr.own_data;

	this->iter_type = attr.iter_type;

	return (*this);
}

big_size_t coords::get_size1d(shape_t &shape) {

	max_size_t ndim = shape.size();

	big_size_t size = 1;

	for (max_size_t i = 0; i < ndim; i++) {

		size *= shape[i];
	}

	return size;
}

shape_t coords::get_strides(shape_t &shape) {

	shape_t strides;

	max_size_t ndim = shape.size();

	if (ndim > 1) {

		strides.reserve(shape.size());

		for (max_size_t i = 1; i < ndim - 1; i++) {

			max_size_t begin = i;
			max_size_t end = ndim - 1;

			strides.push_back(shape.multiply(begin, end) * shape[ndim - 1]);
		}

		strides.push_back(shape[ndim - 1]);
		strides.push_back(1);

	} else {

		strides.push_back(1);
	}

	return strides;
}

void coords::check_strides(shape_t &shape, shape_t &strides) {

	max_size_t ndim = shape.size();

	for (max_size_t i = 0; i < ndim - 1; i++) {

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

	coords new_attr(swaped_shape, tmp_axes, swaped_strides, own_data,
			IteratorType::Linear);

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

coords coords::transpose(bool own_data) const {

	shape_t raxes(this->ndim);

	for (max_size_t i = 0; i < this->ndim; i++) {

		raxes[i] = this->ndim - i - 1;
	}

	coords new_attr = this->permuted(raxes, own_data);

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

	for (max_size_t i = 0; i < this->ndim; i++) {

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

coords coords::reduce_ndim(max_size_t begin, max_size_t end) const {

	if (begin >= end) {
		throw nd::exception("coords::reduce_ndim(...), begin >= end");
	}

	max_size_t out_ndim = end - begin + 1;

	if (this->ndim < out_ndim) {

		throw nd::exception("coords::reduce_ndim(...), out_dim - Out Of Range");
	}

	if (this->ndim <= 2) {

		throw nd::exception("coords::reduce_all(...), this->ndim <= 0");
	}

	shape_t in_shape = this->shape;

	shape_t out_shape = in_shape.reduce_multiply(begin, end).as_std_vec<
			max_size_t>();

	coords out_attr = coords(out_shape);

	return out_attr;
}

coords coords::pad_dim(max_size_t new_ndim) const {

	max_size_t ndim = this->ndim;
	max_size_t max_ndim = std::max(new_ndim, ndim);

	max_size_t pad_size = max_ndim - ndim;

	shape_t shape = this->shape;
	shape_t strides = this->strides;
	shape_t axes = this->axes;

	shape_t new_shape = shape.pad(0, pad_size, 1).as_std_vec<max_size_t>();
	shape_t new_strides = strides.pad(0, pad_size).as_std_vec<max_size_t>();

	max_size_t snew_axis = axes.max(0, axes.size()) + 1;

	shape_t new_axes =
			axes.pad(0, pad_size, snew_axis, 1).as_std_vec<max_size_t>();

	coords new_attr(new_shape, new_axes, new_strides, this->own_data,
			this->iter_type);

	return new_attr;
}

coords coords::pad_dim(max_size_t begin, max_size_t pad_size) const {

	max_size_t ndim = this->ndim;

	if (begin >= ndim) {
		throw nd::exception("coords::pad_dim(...), begin >= end");
	}

	shape_t shape = this->shape;
	shape_t strides = this->strides;
	shape_t axes = this->axes;

	shape_t new_shape = shape.pad(begin, pad_size, 1).as_std_vec<max_size_t>();
	shape_t new_strides = strides.pad(begin, pad_size).as_std_vec<max_size_t>();

	max_size_t snew_axis = axes.max(0, axes.size()) + 1;

	shape_t new_axes = axes.pad(begin, pad_size, snew_axis, 1).as_std_vec<
			max_size_t>();

	coords new_attr(new_shape, new_axes, new_strides, this->own_data,
			this->iter_type);

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

	this->iter_type = IteratorType::Linear;
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
uflag8_t operator &(const shape_t &shape0, const shape_t &shape1) {

	shape_t temp0 = shape0;
	shape_t temp1 = shape1;

	max_size_t size0 = temp0.size();
	max_size_t size1 = temp1.size();

	uflag8_t flag = 1;

	if (size0 == size1) {
		for (max_size_t i = 0; i < size0; i++) {
			if (temp0[i] != temp1[i]) {

				if (temp0[i] == 1 || temp1[i] == 1) {

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

		if (size0 > size1) {
			i = size0 - size1;
			j = 0;
		}

		else {
			i = 0;
			j = size1 - size0;
		}

		while (i < size0 && j < size1) {

			if ((temp0[i] != temp1[j]) && !(temp0[i] == 1 || temp1[j] == 1)) {
				return 0;
			}

			i++;
			j++;
		}

		return 2;
	}
}

// flags: {0: invalid, 1: empty, 2: lower-bound}
uflag8_t operator |(const shape_t &lhs, const shape_t &rhs) {

	shape_t temp_lhs = lhs;
	shape_t temp_rhs = rhs;

	max_size_t n_chunk = std::min(temp_lhs.size(), temp_rhs.size());

// case: invalid
	for (max_size_t i = 0; i < n_chunk; i++) {
		if (temp_lhs[i] < temp_rhs[i]) {
			return 0;
		}
	}

// case: empty
	for (max_size_t i = 0; i < n_chunk; i++) {
		if (temp_lhs[i] == temp_rhs[i]) {
			return 1;
		}
	}

// case: lower-bound
	return 2;
}

// flags: {0: invalid, 1: empty, 2: slice}
uflag8_t operator %(const shape_t &lhs, const shape_t &rhs) {

	shape_t temp_lhs = lhs;
	shape_t temp_rhs = rhs;

	max_size_t n_chunk = std::min(temp_lhs.size(), temp_rhs.size());

	bool lb_exist = 0;

// case: invalid
	if (n_chunk > 0 && temp_lhs[0] < temp_rhs[0]) {

		return 0;
	}

	for (max_size_t i = 1; i < n_chunk; i++) {

		if (temp_lhs[i - 1] > temp_rhs[i - 1]) {

			lb_exist = 1;
		}

		if (temp_lhs[i] < temp_rhs[i] && !lb_exist) {
			return 0;
		}
	}

// case: slice
	for (max_size_t i = 0; i < n_chunk; i++) {
		if (temp_lhs[i] != temp_rhs[i]) {

			return 2;
		}
	}

// case: empty
	return 1;
}

// ============================================= nd =============================================

// used for broadcasting [attr0 & attr1 will be modified]
coords nd::align_dim(coords &attr0, coords &attr1, std::string &&signature) {

	if (!(attr0.shape & attr1.shape)) {

		throw nd::exception(
				signature
						+ "Invalid align_dim(...), coords::shape have to be broadcastable");
	}

	max_size_t ndim1 = attr0.ndim;
	max_size_t ndim2 = attr1.ndim;

	max_size_t max_ndim = std::max(ndim1, ndim2);

	attr0 = attr0.pad_dim(max_ndim);
	attr1 = attr1.pad_dim(max_ndim);

	shape_t shape0 = attr0.shape;
	shape_t shape1 = attr1.shape;

	shape_t out_shape(max_ndim);

	for (max_size_t i = 0; i < max_ndim; i++) {

		out_shape[i] = std::max(shape0[i], shape1[i]);
	}

	coords out_attr = coords(out_shape, true, IteratorType::Pair);

	return out_attr;
}

/*used for linalg-broadcasting [attr0 & attr1 will be modified]
 *
 * axes[i].size() == 2 & axes[i][0] must exactly match axes[i][1]
 *
 * ex.
 *
 * 	nd::linalg::tensordot(...),
 *
 */
coords nd::align_dim(coords &attr0, coords &attr1, vec1d<shape_t> axes,
		std::string &&signature) {

	// parsing nested structure, for validation
	shape_t axes_shape = nd::parser::parse_shape(axes, signature + ", Axes");

	if (axes_shape.size() != 1 || axes_shape[0] != 2) {
		throw nd::exception(
				signature + "Incorrect Axes Format | nd::align_dim(...)");
	}

	max_size_t ndim0 = attr0.ndim;
	max_size_t ndim1 = attr1.ndim;

	shape_t shape0 = attr0.shape;
	shape_t shape1 = attr1.shape;

	shape_t axes0 = attr0.axes;
	shape_t axes1 = attr1.axes;

	if (!(ndim0 >= 2 && ndim1 >= 2)) {

		throw nd::exception(
				signature
						+ "Input dimension has to be greater than or equal 2, ndim >= 2");
	}

	for (max_size_t i = 0; i < axes_shape[0]; i++) {

		if (axes[0][i] >= ndim0 || axes[1][i] >= ndim1) {
			throw nd::exception(signature + "Dimension Out of Range");
		}
		if (shape0[axes[0][i]] != shape1[axes[1][i]]) {

			throw nd::exception(
					signature + "Input: mismatch dimension "
							+ to_string(axes[0][i]) + " != "
							+ to_string(axes[1][i]));

		}

		// [0]
		std::swap(axes0[ndim0 - i - 1], axes0[axes[0][i]]);
		std::swap(axes1[ndim1 - i - 1], axes1[axes[1][i]]);

	}

	// [1]
	vec1d<max_size_t> a_axes = algorithm::a_intersect_b_comp(attr0.axes,
			axes[0]);
	vec1d<max_size_t> b_axes = algorithm::a_intersect_b_comp(attr1.axes,
			axes[1]);

	// [2]
	shape_t out_shape;

	max_size_t i = 0;

	for (auto &ax : a_axes) {
		out_shape.emplace_back(shape0[ax]);

		axes0[i++] = ax;
	}

	i = 0;

	for (auto &ax : b_axes) {
		out_shape.emplace_back(shape1[ax]);

		axes1[i++] = ax;
	}

	coords out_attr(out_shape, true, IteratorType::Pair);

	// [3]
	attr0 = attr0.permuted(axes0, false);
	attr1 = attr1.permuted(axes1, false);

	// [4]
	max_size_t nsum_axes = a_axes.size();

	attr0 = attr0.pad_dim(nsum_axes, nsum_axes);
	attr1 = attr1.pad_dim(0, nsum_axes);

	return out_attr;
}

/*used for linalg-broadcasting [attr0 & attr1 will be modified - pad]
 *
 * ex.
 *
 * 	nd::linalg::matmul(...),
 *
 */
coords nd::align_dim_2d(coords &attr0, coords &attr1, std::string &&signature) {

	max_size_t ndim0 = attr0.ndim;
	max_size_t ndim1 = attr1.ndim;

	shape_t shape0 = attr0.shape;
	shape_t shape1 = attr1.shape;

	if (ndim0 != ndim1 && !nd::state::BroadcastingLevel) {

		throw nd::exception(
				signature
						+ "ndim0 != ndim1 && nd::state::BroadcastingLevel != 2\n\t"
								"nd::state::BroadcastingLevel = 0, "
								"Broadcasting in not allowed");
	}

	if (!(ndim0 >= 2 && ndim1 >= 2)) {

		throw nd::exception(
				signature
						+ "Input dimension has to be greater than or equal 2, ndim >= 2");
	}

	max_size_t dim01 = shape0[ndim0 - 1];
	max_size_t dim12 = shape1[ndim1 - 2];

	if (dim01 != dim12) {

		throw nd::exception("Input: mismatch dimension 0");
	}

	shape_t slice0 = shape0.slice(0, ndim0 - 2).as_std_vec<max_size_t>();
	shape_t slice1 = shape1.slice(0, ndim1 - 2).as_std_vec<max_size_t>();

	uflag8_t valid_op = (slice0 & slice1);

	if (!valid_op) {

		throw nd::exception(signature + ", Inputs: could not be broadcast, "
				"shapes are not aligned for: ndim > 2\n\t");

	}

	// [0]
	max_size_t max_ndim = std::max(ndim0, ndim1);

	// [1]
	attr0 = attr0.pad_dim(max_ndim);
	attr1 = attr1.pad_dim(max_ndim);

	// [2]
	shape0 = attr0.shape;
	shape1 = attr1.shape;

	shape_t out_shape(max_ndim);

	for (max_size_t i = 0; i < max_ndim - 2; i++) {

		out_shape[i] = std::max(shape0[i], shape1[i]);
	}

	out_shape[max_ndim - 2] = shape0[max_ndim - 2];
	out_shape[max_ndim - 1] = shape1[max_ndim - 1];

	coords out_attr = coords(out_shape, true, IteratorType::Pair);

	// [3]
	attr1.swapaxes(max_ndim - 1, max_ndim - 2);

	// [4]
	attr0 = attr0.pad_dim(max_ndim - 1, 1);
	attr1 = attr1.pad_dim(max_ndim - 2, 1);

	return out_attr;
}
