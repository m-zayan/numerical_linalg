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

void test_lu(shape_t shape) {

	nd::matrix<int> mat = nd::random::uniform(1, 100, shape);

	nd::out::print_matrix(mat);

	epline();

	nd::composite<double> lu = nd::linalg::lu<double>(mat);

	nd::out::print_matrix(lu[0]);

	epline();

	nd::out::print_matrix(lu[1]);

	epline();

	nd::matrix<double> mat_ = nd::linalg::matmul<double>(lu[0], lu[1]);

	nd::out::print_matrix(mat_);
}

void test_api::linalg_op() {

//	test_inv( {3, 4, 4 });

	test_lu( {2, 3, 3 });
}

