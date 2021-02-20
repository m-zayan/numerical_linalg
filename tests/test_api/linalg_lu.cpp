/*
 * linalg_lu.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::linalg_lu() {

	nd::matrix<int> mat0 = nd::linalg::eye<int>( { 2, 4, 3 });

	nd::out::print_matrix(mat0);

	std::cout << "\n========================\n";

	nd::matrix<int> mat1 = nd::linalg::eye<int>( { 2, 3, 4 });

	nd::out::print_matrix(mat1);

	std::cout << "\n========================\n";

	nd::matrix<int> mat2 = nd::linalg::eye<int>( { 2, 3, 3 });

	nd::out::print_matrix(mat2);

	std::cout << "\n========================\n";

	nd::matrix<int> mat3 = nd::linalg::eye<int>( { 3, 3 });

}

