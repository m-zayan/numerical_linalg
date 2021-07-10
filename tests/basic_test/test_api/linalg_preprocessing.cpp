/*
 * linalg_preprocessing.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::linalg_preprocessing() {

	shape_t s = { 2, 3, 2 };

	nd::matrix<double> mat = nd::random::uniform(-5, 5, s);

	nd::out::print_matrix(mat);

	std::cout << "\n===============================\n";

	nd::matrix<double, false> tmp = mat.op_view_2d();
	coords attr = tmp._m_coords();

	nd::deprecated::iterator::RandomAccess rndIter(attr);

	flag8_t state = nd::linalg::_h::forward_substitution_step(tmp, rndIter, 0);

	state = nd::linalg::_h::forward_substitution_step(tmp, rndIter, 1);

	nd::out::print_matrix(mat);

	std::cout << "\n===============================\n";

	std::cout << "state [0]: " << static_cast<min_t>(state) << ln;

	std::cout << "\n--------------------\n";

	mat.assign( { 1, 1, 1 }, 0);

	nd::out::print_matrix(mat);

	state = nd::linalg::_h::forward_substitution_step(tmp, rndIter, 1);

	std::cout << "\n--------------------\n";

	std::cout << "state [1]: " << static_cast<min_t>(state) << ln;
}

