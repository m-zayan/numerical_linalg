/*
 * linalg_experimental.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_2d_inplace_transpose() {

	shape_t shape = { 3, 2 };
	nd::matrix<int> mat = nd::random::uniform<int>(0, 5, shape);

	std::cout << "shape :" << mat.shape() << ", own_data: " << mat.own_data()
			<< ln;
	std::cout << "------------\n";

	nd::out::print_matrix(mat);

	std::cout << "\n==============================\n";

	//  nd::v0::linalg::inplace::transpose<int>(..., axes = {...})
	nd::v0::linalg::inplace::transpose<int>(mat, { 1, 0 });

	nd::out::print_matrix(mat);

	std::cout << "\n\n==============================\n";
}

void test_nd_inplace_transpose() {

	shape_t shape = { 3, 2, 2, 2 };

	nd::matrix<int> mat = nd::random::uniform<int>(0, 5, shape);

	std::cout << "shape :" << mat.shape() << ", own_data :" << mat.own_data()
			<< ln;

	std::cout << "\n------------\n";
	std::cout << "data : ";

	nd::out::_h::print_vec1d(mat._m_begin(), 0, mat.size());

	std::cout
			<< "\n\n============ transposed, axes = { 3, 0, 1, 2 } =============\n";

	//  nd::v0::linalg::inplace::transpose<int>(..., axes = {...})
	nd::v0::linalg::inplace::transpose<int>(mat, { 3, 0, 1, 2 });

	std::cout << "shape :" << mat.shape() << ", own_data :" << mat.own_data()
			<< ln;

	std::cout << "\n------------\n";
	std::cout << "data : ";

	nd::out::_h::print_vec1d(mat._m_begin(), 0, mat.size());

	std::cout << "\n=================================\n";
}

void test_api::linalg_experimental() {

	test_2d_inplace_transpose();
}
