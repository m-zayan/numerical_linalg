/*
 * SequentialNdIterator.cpp
 *
 *	Author: Z. Mohamed
 */

#include "SequentialNdIterator.hpp"

SequentialNdIterator::SequentialNdIterator(shape_t shape) {

	this->shape = shape;

	this->dim_bounds = shape.size();
	this->current.fill(this->dim_bounds, 0);

	// last dimension
	this->axis = this->dim_bounds - 1;
	this->mov_axis = this->dim_bounds - 1;

	this->locked = false;
}

shape_t SequentialNdIterator::icurrent() const {

	return this->current;
}

max_size_t SequentialNdIterator::iaxis() {

	return this->axis;
}

shape_t SequentialNdIterator::next() {

	if (this->isLoked()) {

		throw nd::exception("The iterator was locked, if you want to reuse it, "
				"consider using SequentialNdIterator::unlock(), method.");
	}

	this->next_prem();

	return this->current;
}

// update step & return a status flag
flag8_t SequentialNdIterator::proceed(big_t i) {

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
void SequentialNdIterator::next_prem() {

	flag8_t state = this->proceed(0);

	state = this->update_state(state);
}

flag8_t SequentialNdIterator::update_state(flag8_t state) {

	// range: [lower bound, ...]
	big_t lbound = -1;

	while (state == -1) {

		state = this->proceed(lbound);

		lbound -= 1;
	}

	this->axis = this->dim_bounds + lbound;

	return state;
}

void SequentialNdIterator::lock() {

	this->locked = true;
}

bool SequentialNdIterator::isLoked() {

	return this->locked;
}

void SequentialNdIterator::unlock() {

	this->locked = false;
}

void SequentialNdIterator::reset() {

	this->current.fill(this->dim_bounds, 0);
	this->locked = false;
}

SequentialNdIterator::~SequentialNdIterator() {
}

