/*
 * Sequential.cpp
 *
 *	Author: Z. Mohamed
 */

#include "Sequential.hpp"

nd::iterator::Sequential::Sequential(shape_t shape) {

	this->shape = shape;

	this->dim_bounds = shape.size();

	// last dimension
	this->axis = this->dim_bounds - 1;
	this->mov_axis = this->dim_bounds - 1;

	this->current.fill(this->dim_bounds, 0);

	this->locked = false;
}

shape_t nd::iterator::Sequential::icurrent() const {

	return this->current;
}

max_size_t nd::iterator::Sequential::iaxis() {

	return this->axis;
}

void nd::iterator::Sequential::next() {

	if (this->isLoked()) {

		throw nd::exception("The iterator was locked, if you want to reuse it, "
				"consider using Sequential::unlock(), method.");
	}

	this->next_prem();
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
			< this->shape[this->mov_axis + i]) {

		this->current[this->mov_axis + i] += 1;

		return 1;
	}

	// If couldn't proceed with the current axis, request previous update
	else {

		this->current[this->mov_axis + i] = 0;

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
	this->locked = false;
}

nd::iterator::Sequential::~Sequential() {
}

