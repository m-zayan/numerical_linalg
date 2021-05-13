/*
 * linalg_preprocessing.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::linalg_preprocessing() {

	shape_t s = { 2, 3, 2 };

	nd::matrix<int> mat = nd::random::uniform(-5, 5, s);

	nd::out::print_matrix(mat);

	std::cout << "\n===============================\n";

	nd::linalg::_h::partial_pivoting(mat, { 0 }, 0);

	nd::out::print_matrix(mat);

}

