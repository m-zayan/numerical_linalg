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

template<typename T>
nd::matrix<T> matmul(nd::matrix<T> mat1, nd::matrix<T> mat2);

template<typename T>
nd::matrix<T> dot(nd::matrix<T> mat1, nd::matrix<T> mat2);

template<typename T>
nd::matrix<T> inner(nd::matrix<T> mat1, nd::matrix<T> mat2);

template<typename T>
nd::matrix<T> inverse(nd::matrix<T> mat);

template<typename T>
nd::composite<nd::matrix<T>> eigen(nd::matrix<T> mat);

template<typename T>
nd::composite<nd::matrix<T>> svd(nd::matrix<T> mat);

template<typename T>
nd::matrix<T> pseudo_inverse(nd::matrix<T> mat);

template<typename T>
nd::matrix<T> tensordot(nd::matrix<T> mat1, nd::matrix<T> mat2, shape_t axes);

template<typename T>
nd::matrix<T> transpose(shape_t axes);

}

#endif /* SRC_MULTIDIM_LINALG_HPP */
