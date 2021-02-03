/*
 * types.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPES_HPP
#define SRC_TYPES_HPP

#include <vector>
#include <memory>
#include <any>

// Space (n-dimensions) max size = unsigned int
using flag8_t = int8_t;

using min_t = short int;
using max_t = int;
using big_t = long long;

using min_size_t = unsigned short int;
using max_size_t = unsigned int;
using big_size_t = unsigned long long;

template<typename T>
using const_iterator = typename std::vector<T>::iterator;

template<typename T>
using ref_t = std::shared_ptr<T>;

template<typename T>
struct is_dereferenceable: std::false_type {
};

template<typename T>
struct is_dereferenceable<std::shared_ptr<T>> : std::true_type {
};

template<typename T>
struct is_dereferenceable<T*> : std::true_type {
};

#endif /* SRC_TYPES_HPP */
