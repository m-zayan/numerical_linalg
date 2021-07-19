/*
 * iterfunc.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_ITERFUNC_HPP
#define SRC_ITERATORS_ITERFUNC_HPP

#include "./Iterator.hpp"

namespace nd::iterator {

inline big_size_t nd_index_at(const coords &attr, const shape_t &indices) {

	big_size_t index = 0;

	max_size_t naxes = indices.size();

	for (max_size_t i = 0; i < naxes; i++) {
		index += (attr.strides[i] * indices[i]);
	}

	return index;
}

inline void check_slice(Iterator *it, const shape_t &start,
		const shape_t &end) {

	max_size_t ssize = start.size();
	max_size_t esize = end.size();

	if ((ssize > it->ndim) || (esize > it->ndim)) {

		throw nd::exception("Invalid slice nd::iterator::Iterator*, "
				"dimensions out of range");
	}

	uflag8_t valid_s = (it->default_shape | start);
	uflag8_t valid_e = (it->default_shape | end);
	uflag8_t valid_order = (end % start);

	// case: lower-bound <--> [empty is invalid]
	if (valid_s != 2 || valid_e == 0 || valid_order != 2) {

		throw nd::exception("Invalid slice, nd::iterator::Iterator*");
	}
}

inline void slice(Iterator *it, const shape_t &start, const shape_t &end) {

	max_size_t ssize = start.size();
	max_size_t esize = end.size();

	it->reset();

	for (max_size_t i = 0; i < ssize; i++) {

		it->current[i] = start[i];
	}

	for (max_size_t i = 0; i < esize; i++) {

		it->shape[i] = end[i];
	}

	for (max_size_t i = 0; i < it->ndim; i++) {

		it->index1d += (it->current[i] * it->strides[i]);
	}

}

inline void check_indices(Iterator *it, shape_t &indices) {

	if (indices.size() != it->ndim) {
		throw nd::exception("dimensions <--> indices, doesn't match");
	}

	for (max_size_t i = 0; i < it->ndim; i++) {

		if (indices[i] >= it->shape[i]) {

			throw nd::exception("dimensions <--> indices, out of range");
		}
	}
}

}

#endif /* SRC_ITERATORS_ITERFUNC_HPP */
