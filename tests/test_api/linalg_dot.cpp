/*
 * linalg_dot.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::linalg_dot() {

	nd::matrix<int> mat1 = nd::random::uniform<int>(0, 3, { 3, 3, 2 });

	nd::matrix<int> mat2 = nd::random::uniform<int>(0, 3, { 3, 2, 3 });

	std::cout << "=============== (3, 3, 2) ================\n";

	mat1.print_matrix();

	std::cout << "=============== (3, 2, 3) ================\n";

	mat2.print_matrix();

	std::cout << "============= dot: (3, 3, 2) - (3, 2, 3) ================\n";
	nd::matrix<int> result = nd::linalg::dot<int>(mat1, mat2);

	std::cout << "shape :" << result.shape() << " -- own-data :"
			<< result.own_data() << ln;

	std::cout << "---------------------\n";

	result.print_matrix();
}

