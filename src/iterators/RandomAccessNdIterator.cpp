/*
 * RandomAccessNdIterator.cpp
 *
 *	Author: Z. Mohamed
 */

#include "RandomAccessNdIterator.hpp"

RandomAccessNdIterator::RandomAccessNdIterator(coords attr) {

	this->attr = std::move(attr);
}

RandomAccessNdIterator& RandomAccessNdIterator::operator=(const coords &attr) {

	this->attr = std::move(attr);

	return (*this);
}

big_size_t RandomAccessNdIterator::index_at(shape_t indices) const {

	if (indices.size() != this->ndim()) {
		throw nd::exception("dimensions -> indices, doesn't match");
	}

	big_size_t index = 0;

	shape_t strides = this->strides();

	for (max_size_t i = 0; i < this->ndim(); i++) {

		index += (strides[i] * indices[i]);
	}

	return index;
}

big_size_t RandomAccessNdIterator::index_at(big_size_t index_1d) const {

	if (index_1d >= this->size()) {
		throw nd::exception("index_1d, out of range");
	}

	big_size_t index = 0;

	shape_t shape = this->shape();
	shape_t strides = this->strides();
	max_size_t ndim = this->ndim();

	for (max_size_t i = 0; i < ndim; i++) {

		index += (strides[ndim - i - 1] * (index_1d % shape[ndim - i - 1]));
		index_1d /= shape[ndim - i - 1];
	}

	return index;
}

big_size_t RandomAccessNdIterator::size() const {
	return this->attr.size1d;
}

shape_t RandomAccessNdIterator::shape() const {

	return this->attr.shape;
}

shape_t RandomAccessNdIterator::strides() const {

	return this->attr.strides;
}

max_size_t RandomAccessNdIterator::ndim() const {

	return this->attr.ndim;
}

char RandomAccessNdIterator::order() const {

	return this->attr.order;
}

bool RandomAccessNdIterator::own_data() const {

	return this->attr.own_data;
}

RandomAccessNdIterator::~RandomAccessNdIterator() {
}

