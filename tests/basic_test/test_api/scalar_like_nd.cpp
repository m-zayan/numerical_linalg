/*
 * scalar_like_nd.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::scalar_like_nd() {

	shape_t shape = { 3, 3 };

	nd::matrix<int> mat = nd::random::uniform<int>(1, 3, shape);

	nd::out::print_matrix(mat);

	std::cout << "============================\n";

	nd::matrix<int, false> scalar = mat[0][0];

	std::cout << "shape : " << scalar.shape() << ln;
	std::cout << "size : " << scalar.size() << ln;

	std::cout << "-------------------\n";

	nd::out::print_matrix(scalar);

	std::cout << "============================\n";

	nd::out::print_matrix(scalar * scalar);

	std::cout << "============================\n";

	nd::out::print_matrix(mat * scalar);

	std::cout << "============================\n";

	scalar = 100;

	nd::out::print_matrix(mat);

	std::cout << "============================\n";

	std::cout << static_cast<double>(scalar) << ln;

	std::cout << "============================\n";

	nd::matrix<int> res0 = nd::linalg::inner<int>(mat[0], mat[0]);

	nd::out::print_matrix(res0);

	std::cout << "============================\n";

	nd::matrix<int> res1 = nd::linalg::inner<int>(mat[0], scalar);

	nd::out::print_matrix(res1);

}

