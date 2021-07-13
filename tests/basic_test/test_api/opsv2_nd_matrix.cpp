/*
 * opsv2_nd_matrix.cpp
 *
 *      Author: Z. Mohamed
 */

#include "test_api.hpp"

void test_api::opsv2_nd_matrix() {

	shape_t s0 = { 3, 3 };
	nd::matrix<int> m0 = nd::random::uniform<int>(-5, 5, s0);

	nd::out::print_matrix(m0);

	std::cout << "\n==========================\n";

	shape_t s1 = { 3, 3 };
	nd::matrix<int> m1 = nd::linalg::eye<int>(s1);

	nd::out::print_matrix(m1);

	std::cout << "\n==========================\n";

	nd::matrix<int> res = nd::concat<int>( { m0, m1 }, 0);

	nd::out::print_matrix(res.permute( { 1, 0 }));
}
