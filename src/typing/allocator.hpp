/*
 * allocator.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPING_ALLOCATOR_HPP
#define SRC_TYPING_ALLOCATOR_HPP

#include "./types.hpp"

namespace allocator {

template<typename T>
T* val_to_raw_ptr(T val);

template<typename T>
shared_ptr<T> val_to_shared_ptr(T val);

template<typename T>
unique_ptr<T> val_to_unique_ptr(T val);

}

#endif /* SRC_TYPING_ALLOCATOR_HPP */
