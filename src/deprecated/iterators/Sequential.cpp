/*
 * Sequential.cpp
 *
 *	Author: Z. Mohamed
 */

#include "Sequential.hpp"

nd::deprecated::iterator::Sequential::Sequential(coords attr) {

	this->attr = attr;

	this->dim_bounds = this->attr.ndim;

	// last dimension
	this->axis = this->dim_bounds - 1;
	this->mov_axis = this->dim_bounds - 1;

	this->bounds.fill(this->dim_bounds, 0);

	for (max_size_t i = 0; i < this->dim_bounds; i++) {
		this->bounds[i] = (this->shape()[i] - 1) * this->strides()[i];
	}

	this->current.fill(this->dim_bounds, 0);
	this->index_1d = 0;

	this->locked = false;
}

shape_t& nd::deprecated::iterator::Sequential::shape() {

	return this->attr.shape;
}

strides_t& nd::deprecated::iterator::Sequential::strides() {

	return this->attr.strides;
}

max_size_t nd::deprecated::iterator::Sequential::ndim() {

	return this->attr.ndim;
}

shape_t nd::deprecated::iterator::Sequential::indices() const {

	return this->current;
}

big_size_t nd::deprecated::iterator::Sequential::index() const {

	return this->index_1d;
}

max_size_t nd::deprecated::iterator::Sequential::iaxis() {

	return this->axis;
}

bool nd::deprecated::iterator::Sequential::next() {

	if (this->isLocked()) {

		throw nd::exception("The iterator was locked, if you want to reuse it, "
				"consider using Sequential::unlock(), method.");
	}

	this->next_prem();

	return !this->isLocked();
}

// update step & return a status flag
flag8_t nd::deprecated::iterator::Sequential::proceed(big_t i) {

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
void nd::deprecated::iterator::Sequential::next_prem() {

	flag8_t state = this->proceed(0);

	state = this->update_state(state);
}

flag8_t nd::deprecated::iterator::Sequential::update_state(flag8_t state) {

	// range: [lower bound, ...]
	big_t lbound = -1;

	while (state == -1) {

		state = this->proceed(lbound);

		lbound -= 1;
	}

	this->axis = this->dim_bounds + lbound;

	return state;
}

void nd::deprecated::iterator::Sequential::lock() {

	this->locked = true;
}

bool nd::deprecated::iterator::Sequential::isLocked() {

	return this->locked;
}

void nd::deprecated::iterator::Sequential::unlock() {

	this->locked = false;
}

void nd::deprecated::iterator::Sequential::reset() {

	this->current.fill(this->dim_bounds, 0);
	this->index_1d = 0;

	this->axis = this->dim_bounds - 1;

	this->locked = false;
}

void nd::deprecated::iterator::Sequential::slice(shape_t start, shape_t end) {

	if (start.size() > this->ndim() || end.size() > this->ndim()) {

		throw nd::exception("nd::deprecated::iterator::Sequential::slice(...), "
				"Dimensions Out of Range");
	}

	uflag8_t valid_s = (this->shape() | start);
	uflag8_t valid_e = (this->shape() | end);
	uflag8_t valid_order = (end % start);

	if (valid_s == 0 || valid_e == 0 || valid_order == 0) {

		throw nd::exception("Invalid, "
				"nd::deprecated::iterator::Sequential::slice(...)");
	}

	this->reset();

	for (max_size_t i = 0; i < start.size(); i++) {

		this->current[i] = start[i];
	}

	for (max_size_t i = 0; i < end.size(); i++) {

		this->shape()[i] = end[i];
	}

	for (max_size_t i = 0; i < this->ndim(); i++) {

		this->index_1d += (this->current[i] * this->strides()[i]);
	}
}

nd::deprecated::iterator::Sequential::~Sequential() {
}

