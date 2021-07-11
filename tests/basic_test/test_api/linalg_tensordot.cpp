/*
 * linalg_tensordot.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::linalg_tensordot() {

	nd::matrix<int> mat1 = nd::random::uniform<int>(1, 10, { 3, 4, 5 });

	nd::matrix<int> mat2 = nd::random::uniform<int>(1, 10, { 4, 3, 2 });

	std::cout << "=============== (3, 4, 5) ================\n";

	nd::out::_h::print_vec1d(mat1._m_begin(), 0, mat1.size());

	std::cout << "\n\n=============== (4, 3, 2) ================\n";

	nd::out::_h::print_vec1d(mat2._m_begin(), 0, mat2.size());

	std::cout << "\n============= tensordot ================\n";

	nd::matrix<int> result = nd::linalg::tensordot<int>(mat1, mat2, { { 1, 0 },
			{ 0, 1 } });

	std::cout << "shape :" << result.shape() << " -- own-data :"
			<< result.own_data() << ln;
	std::cout << "---------------------\n";

	nd::out::_h::print_vec1d(result._m_begin(), 0, result.size());

}
