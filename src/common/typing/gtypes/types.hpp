/*
 * types.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPING_GTYPES_TYPES_HPP
#define SRC_TYPING_GTYPES_TYPES_HPP

#include <iostream>

#include <initializer_list>

#include <vector>
#include <queue>
#include <functional>

#include <unordered_map>

#include "./stl_wrapper/weak_ptr.hpp"
#include "./stl_wrapper/temporary_queue.hpp"

// types
using bool_t = bool;

using uflag8_t = uint8_t;
using flag8_t = int8_t;

using min_t = short int;
using max_t = int;
using big_t = long long;

using min_size_t = unsigned short int;
using max_size_t = unsigned int;
using big_size_t = unsigned long long;

using float_32 = float;
using float_64 = double;
using float_auto = long double;

template<typename T>
using unique_ptr = std::unique_ptr<T>;

template<typename T>
using shared_ptr = std::shared_ptr<T>;

template<typename T>
using const_iterator = typename std::vector<T>::iterator;

// value - index - pair
template<typename T>
using vipair = std::pair<T, max_size_t>;

template<typename T>
using pair_of = std::pair<T, T>;

// ops
template<typename T>
using val_t = decltype(*std::declval<T>());

template<typename T> struct remove_ptr {

	template<typename ref_t = T>
	static auto rm_t(bool) -> std::remove_reference<val_t<ref_t>>;
	static auto rm_t(...) -> std::remove_cv<T>;

	using type = typename decltype(rm_t(1))::type;
};

template<typename T>
using remove_pointer = typename remove_ptr<T>::type;

// types check
template<typename T>
struct is_shared_ptr: std::false_type {
};

template<typename T>
struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {
};

template<typename T>
struct is_weak_ptr: std::false_type {
};

template<typename T>
struct is_weak_ptr<weak_ptr<T>> : std::true_type {
};

#endif /* SRC_TYPING_GTYPES_TYPES_HPP */
