/*
 * reduction_methods.h
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_LINALG_REDUCTION_METHODS_HPP
#define SRC_LINALG_REDUCTION_METHODS_HPP

#include "../multidim/matrix.hpp"

namespace nd::linalg {

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

}

#endif /* SRC_LINALG_REDUCTION_METHODS_HPP */
