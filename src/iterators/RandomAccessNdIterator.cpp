/*
 * RandomAccessNdIterator.cpp
 *
 *	Author: Z. Mohamed
 */

#include "RandomAccessNdIterator.hpp"

RandomAccessNdIterator::RandomAccessNdIterator(coords attr) {

	this->attr = attr;
}

shape_t RandomAccessNdIterator::indices_at(big_size_t index_1d) const {

	if (index_1d >= this->size()) {
		throw nd::exception("index_1d, out of range");
	}

	shape_t indices(this->ndim());

	shape_t shape = this->shape();
	shape_t strides = this->strides();
	max_size_t ndim = this->ndim();

	for (max_size_t i = 0; i < ndim; i++) {

		indices[ndim - i - 1] = (index_1d % shape[ndim - i - 1]);

		index_1d /= shape[ndim - i - 1];
	}

	return indices;
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

// reversed index
big_size_t RandomAccessNdIterator::reversed_index_at(
		big_size_t index_1d) const {

	if (index_1d >= this->size()) {
		throw nd::exception("index_1d, out of range");
	}

	big_size_t reindex = 0;

	coords prev_attr = this->attr.reverse_permute(false);

	RandomAccessNdIterator prev_rndIter(prev_attr);

	shape_t indices = prev_rndIter.indices_at(index_1d);
	shape_t axes = this->axes();
	shape_t reordered_strides = coords(this->shape()).strides;

	for (max_size_t i = 0; i < this->ndim(); i++) {

		reindex += indices[axes[i]] * reordered_strides[i];
	}

	return reindex;
}

bool RandomAccessNdIterator::is_cycle_root(big_size_t index_1d) const {

	big_size_t size = this->size();

	big_size_t k = index_1d;
	big_size_t xi = size;

	big_size_t max_iter = 0;

	while (true) {

		xi = this->reversed_index_at(k);

		if (xi == index_1d) {
			break;
		}

		else if (xi < index_1d) {
			return false;
		}

		k = xi;

		// debug
		max_iter++;
		if (max_iter == size) {
			throw nd::exception(
					"RandomAccessNdIterator::is_cycle_root(...), has been failed");
		}
	}

	return true;
}
big_size_t RandomAccessNdIterator::size() const {
	return this->attr.size1d;
}

shape_t RandomAccessNdIterator::shape() const {

	return this->attr.shape;
}

shape_t RandomAccessNdIterator::axes() const {

	return this->attr.axes;
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

