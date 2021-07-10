/*
 * Iterator.cpp
 *
 *      Author: Z. Mohamed
 */

#include "Iterator.hpp"

// locked -> true
nd::deprecated::iterator::Iterator::Iterator() :
		index_1d(0), size(0), iter_type(IteratorType::Undefined), locked(false) {

}

nd::deprecated::iterator::Iterator::Iterator(coords attr) :
		index_1d(0), size(attr.size1d), iter_type(attr.iter_type), locked(false) {

}

bool nd::deprecated::iterator::Iterator::next() {

	if (this->iter_type == IteratorType::Scalar) {

		return true;
	}

	else if (this->isLocked()) {

		throw nd::exception("The iterator was locked, if you want to reuse it, "
				"consider using Iterator::reset(), method.");
	}

	this->index_1d += 1;

	if (this->index_1d >= this->size) {

		this->lock();
	}

	return !this->isLocked();
}

big_size_t nd::deprecated::iterator::Iterator::index() const {

	return this->index_1d;
}

bool nd::deprecated::iterator::Iterator::isLocked() {

	return this->locked;
}

void nd::deprecated::iterator::Iterator::lock() {

	this->locked = true;
}

void nd::deprecated::iterator::Iterator::reset() {

	this->index_1d = 0;
	this->locked = false;
}

nd::deprecated::iterator::Iterator::~Iterator() {
}

