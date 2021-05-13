/*
 * PairwiseSequential.cpp
 *
 *      Author: Z. Mohamed
 */

#include "PairwiseSequential.hpp"

nd::iterator::PairwiseSequential::PairwiseSequential(coords attr0,
		coords attr1) {

	coords out_attr = nd::align_dim(attr0, attr1);

	this->attr_list = { attr0, attr1, out_attr };

	this->dim_bounds = out_attr.ndim;

	// last dimension
	this->axis = this->dim_bounds - 1;
	this->mov_axis = this->dim_bounds - 1;

	this->bounds.fill(3, vec1d<big_size_t>(this->dim_bounds));

	for (max_size_t i = 0; i < 3; i++) {

		for (max_size_t j = 0; j < this->dim_bounds; j++) {

			this->ibounds(j, i) = (this->shape(j, i) - 1) * this->strides(j, i);
		}
	}

	this->current.fill(3, shape_t(this->dim_bounds, 0));
	this->index_1d.fill(3, 0);

	this->locked = false;

}
// ============================================================

bool nd::iterator::PairwiseSequential::next() {

	if (this->isLoked()) {

		throw nd::exception("The iterator was locked, if you want to reuse it, "
				"consider using PairwiseSequential::unlock(), method.");
	}

	this->next_prem();

	return !this->isLoked();
}

void nd::iterator::PairwiseSequential::next_prem() {

	flag8_t state = this->proceed(0);

	state = this->update_state(state);
}

flag8_t nd::iterator::PairwiseSequential::update_state(flag8_t state) {

	// range: [lower bound, ...]
	big_t lbound = -1;

	while (state == -1) {

		state = this->proceed(lbound);

		lbound -= 1;
	}

	this->axis = this->dim_bounds + lbound;

	return state;
}

// update step & return a status flag
flag8_t nd::iterator::PairwiseSequential::proceed(big_t i) {

	// If the current, is upper bound, lock the iterator
	if (this->mov_axis + i < 0 || this->mov_axis + i >= this->dim_bounds) {

		this->lock();

		return 0;
	}

	// Current updated. i.e. next() is ready
	else if (this->icurrent(this->mov_axis + i, 2) + 1
			< this->shape(this->mov_axis + i, 2)) {

		// update [indices]
		this->icurrent(this->mov_axis + i, 2) += 1;

		// update [linear index]
		this->iindex(2) += this->strides(this->mov_axis + i, 2);

		// clip
		this->chunk_proceed(this->mov_axis + i, 0);
		this->chunk_proceed(this->mov_axis + i, 1);

		return 1;
	}

	// If couldn't proceed with the current axis, request previous update
	else {

		this->clip(this->mov_axis + i, 2);

		this->clip(this->mov_axis + i, 0);
		this->clip(this->mov_axis + i, 1);

		return -1;
	}

}

void nd::iterator::PairwiseSequential::chunk_proceed(max_size_t axis,
		min_size_t pair_index) {

	if (this->shape(axis, pair_index) == 1) {

		this->clip(axis, pair_index);
	}

	else {

		this->icurrent(axis, pair_index) += 1;
		this->iindex(pair_index) += this->strides(axis, pair_index);

	}

}

void nd::iterator::PairwiseSequential::clip(max_size_t axis,
		min_size_t pair_index) {

	this->icurrent(axis, pair_index) = 0;
	this->iindex(pair_index) -= this->ibounds(axis, pair_index);
}

// ===============================================================

big_size_t& nd::iterator::PairwiseSequential::ibounds(max_size_t axis,
		min_size_t pair_index) {

	return this->bounds[pair_index][axis];
}

max_size_t& nd::iterator::PairwiseSequential::icurrent(max_size_t axis,
		min_size_t pair_index) {

	return this->current[pair_index][axis];
}

big_size_t& nd::iterator::PairwiseSequential::iindex(min_size_t pair_index) {

	return this->index_1d[pair_index];
}

big_size_t nd::iterator::PairwiseSequential::index(min_size_t pair_index) {

	return this->index_1d[pair_index];
}

max_size_t nd::iterator::PairwiseSequential::shape(max_size_t axis,
		min_size_t pair_index) {

	return this->attr_list[pair_index].shape[axis];
}

max_size_t nd::iterator::PairwiseSequential::strides(max_size_t axis,
		min_size_t pair_index) {

	return this->attr_list[pair_index].strides[axis];
}

shape_t nd::iterator::PairwiseSequential::indices(min_size_t pair_index) {

	return this->current[pair_index];
}

max_size_t nd::iterator::PairwiseSequential::iaxis() {

	return this->axis;
}

void nd::iterator::PairwiseSequential::lock() {

	this->locked = true;
}

bool nd::iterator::PairwiseSequential::isLoked() {

	return this->locked;
}

void nd::iterator::PairwiseSequential::unlock() {

	this->locked = false;
}

void nd::iterator::PairwiseSequential::reset() {

	this->current = vec1d<shape_t>(3, shape_t(this->dim_bounds, 0));
	this->index_1d = vec1d<big_size_t>(3);

	this->axis = this->dim_bounds - 1;

	this->locked = false;
}

coords nd::iterator::PairwiseSequential::aligned_coords(min_size_t pair_index) {

	return this->attr_list[pair_index];
}

nd::iterator::PairwiseSequential::~PairwiseSequential() {
}
