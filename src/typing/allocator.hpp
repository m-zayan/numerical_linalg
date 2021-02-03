/*
 * allocator.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPING_ALLOCATOR_HPP_
#define SRC_TYPING_ALLOCATOR_HPP_

#include <vector>
#include <memory>

namespace allocator {

template<typename T>
T* val_to_raw_ptr(T val);

template<typename T>
std::shared_ptr<T> val_to_shared_ptr(T val);

}

#endif /* SRC_TYPING_ALLOCATOR_HPP_ */
