/*
 * types.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPING_UTYPES_TYPES_HPP
#define SRC_TYPING_UTYPES_TYPES_HPP

#include "../common/typing/utypes/mask.hpp"
#include "../common/typing/utypes/bounded_t.cpp"

#include "../common/typing/gtypes/types.hpp"

#include "../common/vec1d.cpp"

template<typename T>
using vec1d_args = vec1d<vec1d<T>>;

template<typename T>
using vec1d_args_wrapper = std::pair<max_size_t, vec1d_args<T>>;

// types
namespace _type {

template<bool own_data, typename T> struct ref_t;

template<typename T> struct ref_t<true, T> {

	using type = shared_ptr<T>;
};

template<typename T> struct ref_t<false, T> {

	using type = weak_ptr<T>;
};

template<typename T, bool ref_holder> struct vec1d_ptr;

template<typename T> struct vec1d_ptr<T, true> {

	using type = shared_ptr<vec1d<T>>;
};

template<typename T> struct vec1d_ptr<T, false> {

	using type = weak_ptr<vec1d<T>>;

};

template<typename T, bool ref_holder>
using data_t = typename vec1d_ptr<T, ref_holder>::type;

}

#endif /* SRC_TYPING_UTYPES_TYPES_HPP */
