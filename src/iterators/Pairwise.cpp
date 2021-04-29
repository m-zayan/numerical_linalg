/*
 * Pairwise.cpp
 *
 *	Author: Z. Mohamed
 */

#include "Pairwise.hpp"

// used for broadcasting [attr0 & attr1 will be modified]
inline coords nd::iterator::align_dim(coords &attr0, coords &attr1) {

	if (!(attr0.shape & attr1.shape)) {

		throw nd::exception(
				"invalid align_dim(...), coords::shape have to be broadcastable");
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

	coords out_attr = coords(out_shape);

	return out_attr;
}

nd::iterator::Pairwise::Pairwise(coords attr0, coords attr1) :
		attr2(nd::iterator::align_dim(attr0, attr1)), attr0(attr0), attr1(
				attr1), rndIter0(RandomAccess(this->attr0)), rndIter1(
				RandomAccess(this->attr1)), rndIter2(RandomAccess(this->attr2)) {

}

shape_t nd::iterator::Pairwise::indices_at(big_size_t index_1d,
		uflag8_t pair_index) const {

	max_size_t ndim = this->attr2.ndim;

	shape_t shape;
	shape_t axes;

	if (pair_index == 0) {
		shape = this->attr0.shape;
		axes = this->attr0.axes;
	}

	else if (pair_index == 1) {
		shape = this->attr1.shape;
		axes = this->attr1.axes;
	}

	else if (pair_index == 2) {

		return this->rndIter2.indices_at(index_1d);
	}

	else {
		throw nd::exception("Invalid pair_index, "
				"nd::iterator::Pairwise::indices_at(..., uflag8_t pair_index)");
	}

	shape_t indices = this->rndIter2.indices_at(index_1d);

	shape_t cliped_indices(ndim);

	// clip indices
	for (max_size_t i = 0; i < ndim; i++) {

		cliped_indices[i] = indices[axes[i]];

		if (shape[i] == 1) {

			cliped_indices[i] = 0;
		}
	}

	return cliped_indices;

}

big_size_t nd::iterator::Pairwise::index_at(big_size_t index_1d,
		uflag8_t pair_index) const {

	shape_t indices = this->indices_at(index_1d, pair_index);

	big_size_t index;

	if (pair_index == 0) {

		index = this->rndIter0.index_at(indices);
	} else if (pair_index == 1) {

		index = this->rndIter1.index_at(indices);
	}

	else {
		index = this->rndIter2.index_at(indices);
	}

	return index;

}

coords nd::iterator::Pairwise::aligned_coords(uflag8_t pair_index) const {

	if (pair_index == 0) {
		return this->attr0;
	}

	else if (pair_index == 1) {
		return this->attr1;
	}

	else if (pair_index == 2) {

		return this->attr2;
	}

	else {
		throw nd::exception("Invalid pair_index, "
				"nd::iterator::Pairwise::indices_at(..., uflag8_t pair_index)");
	}
}

nd::iterator::Pairwise::~Pairwise() {
}

