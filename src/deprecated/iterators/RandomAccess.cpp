/*
 * nd::iterator::RandomAccess.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./RandomAccess.hpp"

nd::iterator::RandomAccess::RandomAccess(coords attr) {

	this->attr = attr;
	this->indices_cache = shape_t(this->ndim());
}

shape_t& nd::iterator::RandomAccess::indices_at(big_size_t index_1d) {

	if (index_1d >= this->size()) {
		throw nd::exception("index_1d, out of range");
	}

	max_size_t ndim = this->ndim();

	for (max_size_t i = 0; i < ndim; i++) {

		this->indices()[ndim - i - 1] =
				(index_1d % this->shape()[ndim - i - 1]);

		index_1d /= this->shape()[ndim - i - 1];
	}

	return this->indices();
}

big_size_t nd::iterator::RandomAccess::nd_index_at(shape_t &indices) {

	if (indices.size() != this->ndim()) {
		throw nd::exception("dimensions <--> indices, doesn't match");
	}

	big_size_t index = 0;

	for (max_size_t i = 0; i < this->ndim(); i++) {

		if (indices[i] >= this->shape()[i]) {

			throw nd::exception("dimensions <--> indices, out of range");
		}

		index += (this->strides()[i] * indices[i]);
	}

	return index;
}

big_size_t nd::iterator::RandomAccess::nd_index_at(shape_t &&indices) {

	if (indices.size() != this->ndim()) {
		throw nd::exception("dimensions -> indices, doesn't match");
	}

	big_size_t index = 0;

	for (max_size_t i = 0; i < this->ndim(); i++) {

		if (indices[i] >= this->shape()[i]) {

			throw nd::exception("dimensions <--> indices, out of range");
		}

		index += (this->strides()[i] * indices[i]);
	}

	return index;
}

big_size_t nd::iterator::RandomAccess::index_at(big_size_t index_1d) {

	if (index_1d >= this->size()) {
		throw nd::exception("index_1d, out of range");
	}

	if (this->iter_type() == 0) {

		return index_1d;
	}

	max_size_t ndim = this->ndim();

	big_size_t index = 0;

	for (max_size_t i = 0; i < ndim; i++) {

		index += (this->strides()[ndim - i - 1]
				* (index_1d % this->shape()[ndim - i - 1]));
		index_1d /= this->shape()[ndim - i - 1];
	}

	return index;
}

// reversed index
big_size_t nd::iterator::RandomAccess::reversed_index_at(big_size_t index_1d,
		coords &prev_attr, nd::iterator::RandomAccess &prev_rndIter,
		strides_t &reordered_strides) {

	if (index_1d >= this->size()) {
		throw nd::exception("index_1d, out of range");
	}

	big_size_t reindex = 0;

	shape_t *indices = &(prev_rndIter.indices_at(index_1d));

	for (max_size_t i = 0; i < this->ndim(); i++) {

		reindex += (*indices)[this->axes()[i]] * reordered_strides[i];
	}

	return reindex;
}

bool nd::iterator::RandomAccess::is_cycle_root(big_size_t index_1d,
		coords &prev_attr, nd::iterator::RandomAccess &prev_rndIter,
		strides_t &reordered_strides) {

	big_size_t size = this->size();

	big_size_t k = index_1d;
	big_size_t xi = size;

	big_size_t max_iter = 0;

	while (true) {

		xi = this->reversed_index_at(k, prev_attr, prev_rndIter,
				reordered_strides);

		if (xi == index_1d) {
			break;
		}

		else if (xi < index_1d) {
			return false;
		}

		k = xi;

		// Debugging
		max_iter++;
		if (max_iter == size) {
			throw nd::exception(
					"nd::iterator::RandomAccess::is_cycle_root(...), has been failed");
		}
	}

	return true;
}

big_size_t nd::iterator::RandomAccess::size() const {
	return this->attr.size1d;
}

shape_t& nd::iterator::RandomAccess::shape() {

	return this->attr.shape;
}

shape_t& nd::iterator::RandomAccess::axes() {

	return this->attr.axes;
}

strides_t& nd::iterator::RandomAccess::strides() {

	return this->attr.strides;
}

shape_t& nd::iterator::RandomAccess::indices() {

	return this->indices_cache;
}

max_size_t nd::iterator::RandomAccess::ndim() const {

	return this->attr.ndim;
}

char nd::iterator::RandomAccess::order() const {

	return this->attr.order;
}

bool nd::iterator::RandomAccess::own_data() const {

	return this->attr.own_data;
}

IteratorType nd::iterator::RandomAccess::iter_type() const {

	return this->attr.iter_type;
}

nd::iterator::RandomAccess::~RandomAccess() {

}

