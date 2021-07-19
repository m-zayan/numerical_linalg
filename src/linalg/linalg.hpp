/*
 * linalg.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_MULTIDIM_LINALG_HPP
#define SRC_MULTIDIM_LINALG_HPP

#include "../multidim/matrix.hpp"

namespace nd::linalg {

/* ================================================================================= */

template<typename T>
nd::matrix<T> eye(shape_t shape);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> augmented(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> augmented(const nd::matrix<T, rf_h> &mat);

/* ================================================================================= */

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> matmul(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> dot(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> inner(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> tensordot(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1, vec1d<shape_t> axes);

template<typename T, bool rf_h>
nd::matrix<T> transpose(const nd::matrix<T, rf_h> &mat, shape_t axes);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> inverse(const nd::matrix<T, rf_h> &mat);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> pseudo_inverse(const nd::matrix<T, rf_h> &mat);

/* ================================================================================= */
/* [decomposition] */

template<typename RT, typename T, bool rf_h>
nd::composite<RT> lu(const nd::matrix<T, rf_h> &mat);

template<typename RT, typename T, bool rf_h>
nd::composite<RT> plu(const nd::matrix<T, rf_h> &mat);

template<typename RT, typename T, bool rf_h>
nd::composite<RT> ldu(const nd::matrix<T, rf_h> &mat);

template<typename RT, typename T, bool rf_h>
nd::composite<RT> qr(const nd::matrix<T, rf_h> &mat);

template<typename RT, typename T, bool rf_h>
nd::composite<RT> svd(const nd::matrix<T, rf_h> &mat);

/* ================================================================================= */

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> upper_triangular(const nd::matrix<T, rf_h> &mat);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> lower_triangular(const nd::matrix<T, rf_h> &mat);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> hessenberg(const nd::matrix<T, rf_h> &mat);

/* ================================================================================= */

/* [eigen] */
template<typename RT, typename T, bool rf_h>
nd::composite<RT> eigen(const nd::matrix<T, rf_h> &mat);

}

/* ================================================================================= */

namespace nd::linalg::inplace {

template<typename T, bool rf_h0, bool rf_h1 = false>
flag8_t partial_pivoting_step(nd::matrix<T, rf_h0> &lhs,
		nd::iterator::Iterator *it, max_size_t ppcols, max_size_t column_index,
		bool pivot = true, bool scale = false, nd::matrix<T, rf_h1> *rhsref =
				nullptr);

template<typename T, bool rf_h0, bool rf_h1 = false>
flag8_t gsubstitution_step(nd::matrix<T, rf_h0> &lhs,
		nd::iterator::Iterator *it, max_size_t gscols, max_size_t column_index,
		bool pivot, nd::matrix<T, rf_h1> *rhsref = nullptr);

/* ================================================================================= */

template<typename T, bool rf_h>
void echelon(nd::matrix<T, rf_h> &mat);

/* ================================================================================= */

template<typename T1, typename T2, bool rf_h0, bool rf_h1>
flag8_t gram_schmidt(nd::matrix<T1, rf_h0> &mat, nd::matrix<T2, rf_h1> &qmat);

template<typename T1, typename T2, bool rf_h0, bool rf_h1>
flag8_t householder(nd::matrix<T1, rf_h0> &mat, nd::matrix<T2, rf_h1> &qmat);

}

namespace nd::v0::linalg::inplace {

// auto-choice <--> [L || U]
template<typename RT, typename T, bool rf_h>
nd::matrix<RT> triangular(const nd::matrix<T, rf_h> &mat);

template<typename T, bool rf_h>
void transpose(nd::matrix<T, rf_h> &mat, shape_t axes);

}

#endif /* SRC_MULTIDIM_LINALG_HPP */
