/*
 * decomposition.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_LINALG_DECOMPOSITION_HPP
#define SRC_LINALG_DECOMPOSITION_HPP

#include "../multidim/matrix.hpp"

namespace nd::linalg {

template<typename T>
nd::composite<nd::matrix<T>> lu(nd::matrix<T> mat);

template<typename T>
nd::composite<nd::matrix<T>> plu(nd::matrix<T> mat);

template<typename T>
nd::composite<nd::matrix<T>> qr(nd::matrix<T> mat);

template<typename T>
nd::composite<nd::matrix<T>> svd(nd::matrix<T> mat);

}

#endif /* SRC_LINALG_DECOMPOSITION_HPP */
