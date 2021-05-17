/*
 * Pairwise.cpp
 *
 *	Author: Z. Mohamed
 */

#include "Pairwise.hpp"

nd::iterator::Pairwise::Pairwise(coords attr0, coords attr1) {

	coords out_attr = nd::align_dim(attr0, attr1);

	this->attr_list = { attr0, attr1, out_attr };

	this->iter_list = vec1d<RandomAccess*>(3);

	for (min_size_t i = 0; i < 3; i++) {

		this->iter_list[i] = new RandomAccess(this->attr_list[i]);

	}

	this->clipped_cache = shape_t(this->attr_list[2].ndim);

}

shape_t& nd::iterator::Pairwise::indices_at(big_size_t index_1d,
		min_size_t pair_index) {

	max_size_t ndim = this->attr_list[2].ndim;

	if (pair_index > 2) {
		throw nd::exception("Invalid pair_index, "
				"nd::iterator::Pairwise::indices_at(..., uflag8_t pair_index)");
	}

	shape_t *current = &(this->iter_of(2).indices_at(index_1d));

	max_size_t axis;
	max_size_t dim_size;

// clip indices
	for (max_size_t i = 0; i < ndim; i++) {

		axis = this->attr_list[pair_index].axes[i];
		dim_size = this->attr_list[pair_index].shape[i];

		this->clipped_indices()[i] = (*current)[axis];

		if (dim_size == 1) {

			this->clipped_indices()[i] = 0;
		}
	}

	return this->clipped_cache;

}

big_size_t nd::iterator::Pairwise::index_at(big_size_t index_1d,
		min_size_t pair_index) {

	shape_t *current = &(this->indices_at(index_1d, pair_index));

	return this->iter_of(pair_index).nd_index_at(*current);

}

coords nd::iterator::Pairwise::aligned_coords(min_size_t pair_index) {

	return this->attr_list[pair_index];
}

shape_t& nd::iterator::Pairwise::clipped_indices() {
	return this->clipped_cache;
}

nd::iterator::RandomAccess& nd::iterator::Pairwise::iter_of(
		min_size_t pair_index) {

	return *(this->iter_list[pair_index]);

}

nd::iterator::Pairwise::~Pairwise() {

	for (min_size_t i = 0; i < 3; i++) {
		delete (this->iter_list[i]);
	}

}

