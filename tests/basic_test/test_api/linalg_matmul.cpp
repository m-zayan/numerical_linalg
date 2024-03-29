/*
 * linalg_matmul.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::linalg_matmul() {

	nd::matrix<int> mat1 = nd::random::uniform<int>(1, 10, { 3, 3, 2 });

	nd::matrix<int> mat2 = nd::random::uniform<int>(1, 10, { 2, 4 });

	std::cout << "=============== (3, 3, 2) ================\n";

	nd::out::_h::print_vec1d(mat1._m_begin(), 0, mat1.size());

	std::cout << "\n\n=============== (2, 4) ================\n";

	nd::out::_h::print_vec1d(mat2._m_begin(), 0, mat2.size());

	std::cout << "\n============= matmul: (3, 3, 2) - (2, 4) ================\n";
	nd::matrix<int> result = nd::linalg::matmul<int>(mat1, mat2);

	std::cout << "shape :" << result.shape() << " -- own-data :"
			<< result.own_data() << ln;
	std::cout << "---------------------\n";

	nd::out::_h::print_vec1d(result._m_begin(), 0, result.size());
}
