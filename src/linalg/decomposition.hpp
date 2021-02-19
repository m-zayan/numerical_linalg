/*
 * decomposition.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_LINALG_DECOMPOSITION_HPP
#define SRC_LINALG_DECOMPOSITION_HPP

#include "../multidim/matrix.hpp"

namespace nd::linalg {

template<typename RT, typename T, bool rf_h>
nd::composite<nd::matrix<RT>> lu(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::composite<nd::matrix<RT>> plu(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::composite<nd::matrix<RT>> qr(nd::matrix<T, rf_h> mat);

template<typename RT, typename T, bool rf_h>
nd::composite<nd::matrix<RT>> svd(nd::matrix<T, rf_h> mat);

}

#endif /* SRC_LINALG_DECOMPOSITION_HPP */
