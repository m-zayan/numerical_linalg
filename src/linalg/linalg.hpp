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

template<typename RT>
nd::matrix<RT> eye(shape_t shape, max_t dshift = 0);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> diag(const nd::matrix<T, rf_h> &mat, max_t dshift = 0);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> diag2d(const nd::matrix<T, rf_h> &mat, max_t dshift = 0);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> mask_diag(const nd::matrix<T, rf_h> &mat, max_t dshift = 0);

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> augmented(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> augmented(const nd::matrix<T, rf_h> &mat);

/* ================================================================================= */

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> det(const nd::matrix<T, rf_h> &mat);

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> norm(const nd::matrix<T, rf_h> &mat, flag8_t n_ord,
		max_size_t axis, bool keepdims = false);

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

template<typename RT = float_auto, typename T, bool rf_h>
nd::matrix<RT> inverse(const nd::matrix<T, rf_h> &mat, bool pivot = true);

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

template<typename T1, typename T2 = float_auto, typename T3 = mask_t,
		bool rf_h0, bool rf_h1 = false, bool rf_h2 = false>
flag8_t partial_pivoting_step(nd::matrix<T1, rf_h0> &lhs,
		nd::iterator::Iterator *it, max_size_t ppcols, max_size_t column_index,
		uflag8_t state = 0, nd::matrix<T2, rf_h1> *rhsref = nullptr,
		nd::matrix<T3, rf_h2> *perm = nullptr);

template<typename T1, typename T2 = float_auto, typename T3 = mask_t,
		bool rf_h0, bool rf_h1 = false, bool rf_h2 = false>
flag8_t psubstitution_step(nd::matrix<T1, rf_h0> &lhs,
		nd::iterator::Iterator *it, max_size_t pscols, max_size_t column_index,
		bool pivot, uflag8_t state = 0, nd::matrix<T2, rf_h1> *rhsref = nullptr,
		nd::matrix<T3, rf_h2> *perm = nullptr);

template<typename T1, typename T2 = float_auto, typename T3 = mask_t,
		bool rf_h0, bool rf_h1 = false, bool rf_h2 = false>
flag8_t gsubstitution_step(nd::matrix<T1, rf_h0> &lhs,
		nd::iterator::Iterator *it, max_size_t gscols, max_size_t column_index,
		bool pivot, uflag8_t state = 0, nd::matrix<T2, rf_h1> *rhsref = nullptr,
		nd::matrix<T3, rf_h2> *perm = nullptr);

/* ================================================================================= */

template<typename T, bool rf_h>
void echelon(nd::matrix<T, rf_h> &mat);

/* ================================================================================= */

template<typename T1, typename T2, bool rf_h0, bool rf_h1>
flag8_t gram_schmidt(nd::matrix<T1, rf_h0> &mat, nd::matrix<T2, rf_h1> &qmat);

template<typename T1, typename T2, bool rf_h0, bool rf_h1>
flag8_t householder(nd::matrix<T1, rf_h0> &mat, nd::matrix<T2, rf_h1> &qmat);

/* ================================================================================= */

template<typename T, bool rf_h>
void diag_add(nd::matrix<T, rf_h> &mat, T value, max_t dshift = 0);

template<typename T, bool rf_h>
void diag_factor_out(nd::matrix<T, rf_h> &m0, max_t dshift = 0);

}

namespace nd::v0::linalg::inplace {

// auto-choice <--> [L || U]
template<typename T, bool rf_h>
void triangular(nd::matrix<T, rf_h> &mat);

template<typename T, bool rf_h>
void transpose(nd::matrix<T, rf_h> &mat, shape_t axes);

}

#endif /* SRC_MULTIDIM_LINALG_HPP */
