/*
 * test_api.h
 *
 *	Author: Z. Mohamed
 */

#ifndef TEST_API_TEST_API_H_
#define TEST_API_TEST_API_H_

#include <chrono>
#include <assert.h>
#include <math.h>

#include "../src/multidim/matrix.cpp"
#include "../src/linalg/linalg.cpp"

#define ln '\n'

namespace test_api {

void sum_alg(unsigned int test_size);
void alloc_nd_matrix();
void linalg_matmul();
void linalg_dot();

}

#endif /* TEST_API_TEST_API_H_ */
