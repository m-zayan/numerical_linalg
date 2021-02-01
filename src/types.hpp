/*
 * types.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPES_HPP
#define SRC_TYPES_HPP

#include <vector>
#include <memory>

// Space (n-dimensions) max size = unsigned int
using min_size_t = unsigned short int;
using max_size_t = unsigned int;
using big_size_t = unsigned long long;

template<typename T>
using const_iterator = typename std::vector<T>::iterator;

template<typename T>
using ref_t = std::shared_ptr<T>;

#endif /* SRC_TYPES_HPP */
