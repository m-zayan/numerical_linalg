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

	nd::out::_h::print_vec1d(mat1._m_begin(), 0, mat1.size());

	std::cout << "\n\n=============== (3, 2, 3) ================\n";

	nd::out::_h::print_vec1d(mat2._m_begin(), 0, mat2.size());

	std::cout
			<< "\n\n============= dot: (3, 3, 2) - (3, 2, 3) ================\n";
	nd::matrix<int> result = nd::linalg::dot<int>(mat1, mat2);

	std::cout << "shape :" << result.shape() << " -- own-data :"
			<< result.own_data() << ln;

	std::cout << "---------------------\n";

	nd::out::_h::print_vec1d(result._m_begin(), 0, result.size());
}

