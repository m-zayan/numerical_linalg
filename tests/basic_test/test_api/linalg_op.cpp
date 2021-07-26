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

void test_plu(shape_t shape) {

	nd::matrix<int> mat = nd::random::uniform(-5, 10, shape);

	nd::out::print_matrix(mat);

	epline();

	nd::composite<double> plu = nd::linalg::plu<double>(mat);

	for (max_size_t i = 0; i < 3; i++) {

		nd::out::print_matrix(plu[i]);
		epline();
	}

	nd::matrix<double> mat_ = nd::linalg::matmul<double>(plu[0], plu[1]);

	mat_ = nd::linalg::matmul<double>(mat_, plu[2]);

	nd::out::print_matrix(mat_);
}

void test_ldu(shape_t shape) {

	nd::matrix<int> mat = nd::random::uniform(-5, 10, shape);

	nd::out::print_matrix(mat);

	epline();

	nd::composite<double> ldu = nd::linalg::ldu<double>(mat);

	for (max_size_t i = 0; i < 3; i++) {

		nd::out::print_matrix(ldu[i]);
		epline();
	}

	nd::matrix<double> mat_ = nd::linalg::matmul<double>(ldu[0], ldu[1]);

	mat_ = nd::linalg::matmul<double>(mat_, ldu[2]);

	nd::out::print_matrix(mat_);
}

void test_upper(shape_t shape) {

	nd::matrix<int> mat = nd::random::uniform(1, 100, shape);

	nd::out::print_matrix(mat);

	epline();

	nd::matrix<double> U = nd::linalg::upper_triangular<double>(mat);

	nd::out::print_matrix(U);

	epline();
}

void test_lower(shape_t shape) {

	nd::matrix<int> mat = nd::random::uniform(1, 100, shape);

	nd::out::print_matrix(mat);

	epline();

	nd::matrix<double> U = nd::linalg::lower_triangular<double>(mat);

	nd::out::print_matrix(U);

	epline();
}

void test_echelon(shape_t shape) {

	nd::matrix<double> mat = nd::random::uniform(1, 100, shape);

	nd::out::print_matrix(mat);

	epline();

	nd::linalg::inplace::echelon(mat);

	nd::out::print_matrix(mat);

	epline();
}

void test_api::linalg_op() {

//	test_inv( {3, 4, 4 });

//	test_lu( { 2, 3, 3 });

//	test_plu( { 2, 3, 3 });

//	test_ldu( { 2, 3, 3 });

//	test_upper( {2, 3, 3 });

//	test_lower({2, 3, 3});

//	test_echelon( { 2, 3, 3 });
}

