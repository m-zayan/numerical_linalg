/*
 * allocator.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_TYPING_ALLOCATOR_HPP
#define SRC_TYPING_ALLOCATOR_HPP

#include "./types.hpp"

namespace allocator {

template<typename T>
shared_ptr<vec1d<T>> init_data(big_size_t size) {

	return shared_ptr<vec1d<T>>(new vec1d<T>(size));
}

template<typename T>
shared_ptr<vec1d<T>> init_data(big_size_t size, T val) {

	return shared_ptr<vec1d<T>>(new vec1d<T>(size, val));
}

}

#endif /* SRC_TYPING_ALLOCATOR_HPP */
