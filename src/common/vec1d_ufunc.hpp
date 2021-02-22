/*
 * vec1d_ufunc.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_COMMON_VEC1D_UFUNC_HPP
#define SRC_COMMON_VEC1D_UFUNC_HPP

#include <functional>

namespace _v_ops {

template<typename RT, typename T1, typename T2>
std::function<void(RT&, T1, T2)> mul = [](RT &v0, T1 v1, T2 v2) {

	v0 = v1 * v2;
};

template<typename RT, typename T1, typename T2>
std::function<void(RT&, T1, T2)> div = [](RT &v0, T1 v1, T2 v2) {

	v0 = v1 / v2;
};

template<typename RT, typename T1, typename T2>
std::function<void(RT&, T1, T2)> add = [](RT &v0, T1 v1, T2 v2) {

	v0 = v1 + v2;
};

template<typename RT, typename T1, typename T2>
std::function<void(RT&, T1, T2)> sub = [](RT &v0, T1 v1, T2 v2) {

	v0 = v1 - v2;
};

template<typename RT, typename T1, typename T2>
std::function<void(RT&, T1, T2)> bool_equal = [](RT &v0, T1 v1, T2 v2) {

	v0 = (v1 == v2);
};
}

#endif /* SRC_COMMON_VEC1D_UFUNC_HPP */
