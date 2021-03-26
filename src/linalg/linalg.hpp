/*
 * linalg.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_MULTIDIM_LINALG_HPP
#define SRC_MULTIDIM_LINALG_HPP

#include "../multidim/matrix.hpp"

namespace nd::linalg {

template<typename T>
nd::matrix<T> eye(shape_t shape);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> matmul(nd::matrix<T1, rf_h0> m1, nd::matrix<T2, rf_h1> m2);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> dot(nd::matrix<T1, rf_h0> m1, nd::matrix<T2, rf_h1> m2);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> inner(nd::matrix<T1, rf_h0> m1, nd::matrix<T2, rf_h1> m2);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> tensordot(nd::matrix<T1, rf_h0> m1, nd::matrix<T2, rf_h1> m2,
		shape_t axes);

template<typename T, bool rf_h>
nd::matrix<T> transpose(nd::matrix<T, rf_h> mat, shape_t axes);

//template<typename T, bool rf_h>
//void inplace_transpose(nd::matrix<T, rf_h> &mat, shape_t axes);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> inverse(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> pseudo_inverse(nd::matrix<T, rf_h> mat);

//template<typename T>
//nd::composite<nd::matrix<T>> eigen(nd::matrix<T> mat);

}

#endif /* SRC_MULTIDIM_LINALG_HPP */

