/*
 * types.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPING_GTYPES_TYPES_HPP
#define SRC_TYPING_GTYPES_TYPES_HPP

#include <vector>
#include <queue>

#include "./stl_wrapper/weak_ptr.hpp"

// types
using bool_t = bool;
using flag8_t = int8_t;

using min_t = short int;
using max_t = int;
using big_t = long long;

using min_size_t = unsigned short int;
using max_size_t = unsigned int;
using big_size_t = unsigned long long;

template<typename T>
using unique_ptr = std::unique_ptr<T>;

template<typename T>
using shared_ptr = std::shared_ptr<T>;

template<typename T>
using const_iterator = typename std::vector<T>::iterator;

template<bool own_data, typename T> struct ref_t;

template<typename T> struct ref_t<true, T> {

	using type = shared_ptr<T>;
	using val_t = T;
};

template<typename T> struct ref_t<false, T> {

	using type = weak_ptr<T>;
	using val_t = T;
};

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
