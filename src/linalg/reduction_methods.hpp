/*
 * reduction_methods.h
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_LINALG_REDUCTION_METHODS_HPP
#define SRC_LINALG_REDUCTION_METHODS_HPP

#endif /* SRC_LINALG_REDUCTION_METHODS_HPP */

#include "../multidim/matrix.hpp"

namespace nd::linalg {

template<typename T>
matrix<T> upper_triangular(nd::matrix<T> mat);

template<typename T>
matrix<T> lower_triangular(nd::matrix<T> mat);

template<typename T>
matrix<T> triangular(nd::matrix<T> mat);

template<typename T>
matrix<T> echelon(nd::matrix<T> mat);

template<typename T>
matrix<T> hessenberg(nd::matrix<T> mat);

}
