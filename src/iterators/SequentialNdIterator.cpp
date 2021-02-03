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
	this->cur_dim = this->dim_bounds - 1;

	this->locked = false;
}

vec1d<max_size_t> SequentialNdIterator::icurrent() {

	return this->current;
}

vec1d<max_size_t> SequentialNdIterator::next() {

	if (this->isLoked()) {

		throw nd::exception("The iterator was locked, if you want to reuse it, "
				"consider using SequentialNdIterator::rest(), method.");
	}

	this->next_prem();

	return this->current;
}

// update step & return a status flag
flag8_t SequentialNdIterator::proceed(big_t i) {

	// If the current, is upper bound, request locking the iterator
	if (this->cur_dim + i < 0 || this->cur_dim + i >= this->dim_bounds) {

		this->lock();

		return 0;
	}

	// Current updated. i.e. next() is ready
	else if (this->current[this->cur_dim + i] + 1
			< this->shape[this->cur_dim + i]) {

		this->current[this->cur_dim + i] += 1;

		return 1;
	}

	// If couldn't proceed with the current dimension, request previous update
	else {

		this->current[this->cur_dim + i] = 0;

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

	return state;
}

void SequentialNdIterator::lock() {

	this->locked = true;
}

bool SequentialNdIterator::isLoked() {

	return this->locked;
}

void SequentialNdIterator::reset() {

	this->locked = false;
}

SequentialNdIterator::~SequentialNdIterator() {
}

