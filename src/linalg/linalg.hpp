/*
 * linalg.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_MULTIDIM_LINALG_HPP
#define SRC_MULTIDIM_LINALG_HPP

#include "../multidim/matrix.hpp"

namespace nd::linalg::_h {

template<typename T, bool ref_h>
void partial_pivoting(nd::matrix<T, ref_h> &mat, shape_t chunk_indices,
		max_size_t column_index);

}

namespace nd::linalg {

template<typename T>
nd::matrix<T> eye(shape_t shape);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> matmul(const nd::matrix<T1, rf_h0> &m1,
		const nd::matrix<T2, rf_h1> &m2);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> dot(const nd::matrix<T1, rf_h0> &m1,
		const nd::matrix<T2, rf_h1> &m2);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> inner(const nd::matrix<T1, rf_h0> &m1,
		const nd::matrix<T2, rf_h1> &m2);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> tensordot(const nd::matrix<T1, rf_h0> &m1,
		const nd::matrix<T2, rf_h1> &m2, shape_t axes);

template<typename T, bool rf_h>
nd::matrix<T> transpose(nd::matrix<T, rf_h> mat, shape_t axes);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> inverse(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> pseudo_inverse(nd::matrix<T, rf_h> mat);

// decomposition
template<typename RT, typename T, bool rf_h>
nd::composite<nd::matrix<RT>> lu(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::composite<nd::matrix<RT>> plu(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::composite<nd::matrix<RT>> qr(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::composite<nd::matrix<RT>> svd(nd::matrix<T, rf_h> mat);

// reduction-methods
template<typename RT, typename T, bool rf_h>
nd::matrix<RT> upper_triangular(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> lower_triangular(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> triangular(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> echelon(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> hessenberg(nd::matrix<T, rf_h> mat);

// eigen
template<typename T>
nd::composite<nd::matrix<T>> eigen(nd::matrix<T> mat);

}

namespace nd::linalg::inplace {

//template<typename T, bool rf_h>
//void swapaxes(nd::matrix<T, rf_h> &mat, max_size_t ax0,
//		max_size_t ax1);

template<typename T, bool rf_h>
void transpose(nd::matrix<T, rf_h> &mat, shape_t axes);

}

#endif /* SRC_MULTIDIM_LINALG_HPP */

