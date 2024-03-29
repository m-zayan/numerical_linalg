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

#include "../../../src/io/stdout.hpp"

#define ln '\n'

inline void epline(max_size_t size = 50) {
	std::cout << std::string(size, '=') << ln;
}

inline void eppline(max_size_t size = 50) {
	std::cout << ln << std::string(size, '=') << ln;
}

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
void linalg_experimental();
void nd_broadcasting();
void ops_nd_matrix();
void linalg_preprocessing();
void linalg_op();
void scalar_like_nd();
void opsv2_nd_matrix();

}

#endif /* TEST_API_TEST_API_HPP */
