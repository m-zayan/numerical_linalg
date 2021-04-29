/*
 * Pairwise.cpp
 *
 *	Author: Z. Mohamed
 */

#include "Pairwise.hpp"

// used for broadcasting
inline coords nd::iterator::align_dim(coords attr1, coords attr2) {

	if (!(attr1.shape & attr2.shape)) {

		throw nd::exception(
				"invalid align_dim(...), coords::shape have to be broadcastable");
	}

	max_size_t ndim1 = attr1.ndim;
	max_size_t ndim2 = attr2.ndim;

	max_size_t max_ndim = std::max(ndim1, ndim2);

	coords new_attr1 = attr1.pad_dim(max_ndim);
	coords new_attr2 = attr2.pad_dim(max_ndim);

	shape_t shape1 = new_attr1.shape;
	shape_t shape2 = new_attr2.shape;

	shape_t out_shape(max_ndim);

	for (max_size_t i = 0; i < max_ndim; i++) {

		out_shape[i] = std::max(shape1[i], shape2[i]);
	}

	coords out_attr = coords(out_shape);

	return out_attr;
}

nd::iterator::Pairwise::Pairwise(coords attr1, coords attr2) :
		attr1(attr1), attr2(attr2), aligned_attr(
				nd::iterator::align_dim(attr1, attr2)), rndIter(
				RandomAccess(this->aligned_attr)) {

}

shape_t nd::iterator::Pairwise::indices_at(big_size_t index_1d,
		uflag8_t pair_index) const {

	max_size_t ndim = this->aligned_attr.ndim;

	shape_t shape;

	if (pair_index == 0) {
		shape = this->attr1.shape;
	}

	else if (pair_index == 1) {
		shape = this->attr2.shape;
	}

	else if (pair_index == 2) {

		return this->rndIter.indices_at(index_1d);
	}

	else {
		throw nd::exception("Invalid pair_index, "
				"nd::iterator::Pairwise::indices_at(..., uflag8_t pair_index)");
	}

	shape_t indices = this->rndIter.indices_at(index_1d);

	// clip indices
	for (max_size_t i = 0; i < ndim; i++) {

		if (shape[i] == 1) {

			indices[i] = 0;
		}

	}

	return indices;
}

big_size_t nd::iterator::Pairwise::index_at(big_size_t index_1d,
		uflag8_t pair_index) const {

	shape_t indices = this->indices_at(index_1d, pair_index);

	big_size_t index = this->rndIter.index_at(indices);

	return index;
}

coords nd::iterator::Pairwise::aligned_coords() const {
	return this->aligned_attr;
}

nd::iterator::Pairwise::~Pairwise() {
}

