/*
 * reduction_methods.h
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_LINALG_REDUCTION_METHODS_HPP
#define SRC_LINALG_REDUCTION_METHODS_HPP

#include "../multidim/matrix.hpp"

namespace nd::linalg {

template<typename T>
nd::matrix<T> upper_triangular(nd::matrix<T> mat);

template<typename T>
nd::matrix<T> lower_triangular(nd::matrix<T> mat);

template<typename T>
nd::matrix<T> triangular(nd::matrix<T> mat);

template<typename T>
nd::matrix<T> echelon(nd::matrix<T> mat);

template<typename T>
nd::matrix<T> hessenberg(nd::matrix<T> mat);

}

#endif /* SRC_LINALG_REDUCTION_METHODS_HPP */
