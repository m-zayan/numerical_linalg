/*
 * Pairwise.cpp
 *
 *	Author: Z. Mohamed
 */

#include "Pairwise.hpp"

// =================================================================

bounded_t<max_size_t> nd::mem::AUX_SIZE( { 2, 512, 1028, 2048 }, "AUX_SIZE",
		2048);

bounded_t<uflag8_t> nd::state::BroadcastingLevel( { 0, 1, 2 },
		"BroadcastingLevel", 2);

// =================================================================

// used for broadcasting [attr0 & attr1 will be modified]
coords nd::iterator::align_dim(coords &attr0, coords &attr1) {

	if (!(attr0.shape & attr1.shape)) {

		throw nd::exception(
				"Invalid align_dim(...), coords::shape have to be broadcastable");
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

	coords out_attr = coords(out_shape, true, 2);

	return out_attr;
}

// ###########################################################################################################################

nd::iterator::Pairwise::Pairwise(coords attr0, coords attr1) {

	coords out_attr = nd::iterator::align_dim(attr0, attr1);

	this->attr_list = { attr0, attr1, out_attr };

	this->iter_list = vec1d<RandomAccess*>(3);

	for (min_size_t i = 0; i < 3; i++) {

		this->iter_list[i] = allocator::val_to_raw_ptr(
				RandomAccess(this->attr_list[i]));

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

coords& nd::iterator::Pairwise::aligned_coords(min_size_t pair_index) {

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

