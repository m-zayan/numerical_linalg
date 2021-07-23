/*
 * linalg_op.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_inv(shape_t shape) {

	nd::matrix<int> mat = nd::random::uniform(1, 100, shape);

	nd::out::print_matrix(mat);

	epline();

	nd::matrix<double> inv = nd::linalg::inverse(mat);

	nd::out::print_matrix(inv);

	epline();

	nd::matrix<double> I = nd::linalg::matmul<double>(mat, inv);

	nd::out::print_matrix(I);

	epline();
}

void test_api::linalg_op() {

	test_inv( {2, 3, 3 });
}

