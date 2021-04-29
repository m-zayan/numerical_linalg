/*
 * ops_nd_matrix.cpp
 *
 *	Author: Z. Mohamed
 */

#include "test_api.hpp"

void test_api::ops_nd_matrix() {

	shape_t s0 = { 3, 3 };
	nd::matrix<int> m0 = nd::random::uniform(0, 10, s0);

	nd::out::print_matrix(m0);

	std::cout << "\n ============================= \n";

	nd::matrix<int> out0 = nd::numeric::min<int>(m0, 1);

	std::cout << " shape : " << out0.shape() << "\n -------------- \n";

	nd::out::print_matrix(out0);

	std::cout << "\n ============================= \n";

	nd::matrix<double> out1 = nd::numeric::argmin<double>(m0, 1);

	std::cout << " shape : " << out1.shape() << "\n -------------- \n";

	nd::out::print_matrix(out1 + 0.5);

	std::cout << "\n ============================= \n";

	nd::matrix<int> out2 = nd::numeric::max<int>(m0, 1);

	std::cout << " shape : " << out2.shape() << "\n -------------- \n";

	nd::out::print_matrix(out2);

	std::cout << "\n ============================= \n";

	nd::matrix<max_size_t> out3 = nd::numeric::argmax<max_size_t>(m0, 1);

	std::cout << " shape : " << out3.shape() << "\n -------------- \n";

	nd::out::print_matrix(out3 + 0.5);

	std::cout << "\n ============================= \n";

	nd::matrix<double> out4 = nd::numeric::sum<double>(m0, 1);

	std::cout << " shape : " << out4.shape() << "\n -------------- \n";

	nd::out::print_matrix(out4 + 0.5);
}
