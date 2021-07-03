/*
 * test_api.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef TEST_API_TEST_API_HPP
#define TEST_API_TEST_API_HPP

#include <chrono>
#include <assert.h>
#include <math.h>

#include "../../../src/multidim/matrix.cpp"
#include "../../../src/linalg/linalg.cpp"

#define ln '\n'

namespace test_api {

void sum_alg(unsigned int test_size);
void alloc_nd_matrix();
void linalg_matmul();
void linalg_tensordot();
void linalg_dot();
void linalg_transpose();
void linalg_echelon();
void linalg_hessenberg();
void reorder_copy();
void linalg_inplace();
void nd_broadcasting();
void ops_nd_matrix();
void linalg_preprocessing();
void linalg_lu();
void scalar_like_nd();

}

#endif /* TEST_API_TEST_API_HPP */
