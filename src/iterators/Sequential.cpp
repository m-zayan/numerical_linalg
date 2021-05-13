/*
 * Sequential.cpp
 *
 *	Author: Z. Mohamed
 */

#include "Sequential.hpp"

nd::iterator::Sequential::Sequential(coords attr) {

	this->attr = attr;

	this->dim_bounds = this->attr.ndim;

	// last dimension
	this->axis = this->dim_bounds - 1;
	this->mov_axis = this->dim_bounds - 1;

	this->bounds = shape_t(this->dim_bounds);

	for (max_size_t i = 0; i < this->dim_bounds; i++) {
		this->bounds[i] = (this->shape()[i] - 1) * this->strides()[i];
	}

	this->current.fill(this->dim_bounds, 0);
	this->index_1d = 0;

	this->locked = false;
}

shape_t& nd::iterator::Sequential::shape() {

	return this->attr.shape;
}

shape_t& nd::iterator::Sequential::strides() {

	return this->attr.strides;
}

shape_t nd::iterator::Sequential::icurrent() const {

	return this->current;
}

big_size_t nd::iterator::Sequential::index() const {

	return this->index_1d;
}

max_size_t nd::iterator::Sequential::iaxis() {

	return this->axis;
}

bool nd::iterator::Sequential::next() {

	if (this->isLoked()) {

		throw nd::exception("The iterator was locked, if you want to reuse it, "
				"consider using Sequential::unlock(), method.");
	}

	this->next_prem();

	return !this->isLoked();
}

// update step & return a status flag
flag8_t nd::iterator::Sequential::proceed(big_t i) {

	// If the current, is upper bound, lock the iterator
	if (this->mov_axis + i < 0 || this->mov_axis + i >= this->dim_bounds) {

		this->lock();

		return 0;
	}

	// Current updated. i.e. next() is ready
	else if (this->current[this->mov_axis + i] + 1
			< this->shape()[this->mov_axis + i]) {

		// update [indices]
		this->current[this->mov_axis + i] += 1;

		// update [linear index]
		this->index_1d += this->strides()[this->mov_axis + i];

		return 1;
	}

	// If couldn't proceed with the current axis, request previous update
	else {

		// [indices]
		this->current[this->mov_axis + i] = 0;

		// [linear index]
		this->index_1d -= this->bounds[this->mov_axis + i];

		return -1;
	}

}
void nd::iterator::Sequential::next_prem() {

	flag8_t state = this->proceed(0);

	state = this->update_state(state);
}

flag8_t nd::iterator::Sequential::update_state(flag8_t state) {

	// range: [lower bound, ...]
	big_t lbound = -1;

	while (state == -1) {

		state = this->proceed(lbound);

		lbound -= 1;
	}

	this->axis = this->dim_bounds + lbound;

	return state;
}

void nd::iterator::Sequential::lock() {

	this->locked = true;
}

bool nd::iterator::Sequential::isLoked() {

	return this->locked;
}

void nd::iterator::Sequential::unlock() {

	this->locked = false;
}

void nd::iterator::Sequential::reset() {

	this->current.fill(this->dim_bounds, 0);
	this->index_1d = 0;

	this->axis = this->dim_bounds - 1;

	this->locked = false;
}

nd::iterator::Sequential::~Sequential() {
}

