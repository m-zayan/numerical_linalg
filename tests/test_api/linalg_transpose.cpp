/*
 * linalg_transpose.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::linalg_transpose() {

	shape_t shape0 = { 3, 2 };
	nd::matrix<int> mat0 = nd::random::uniform<int>(0, 5, shape0);

	std::cout << "shape :" << mat0.shape() << ", " << mat0.own_data() << ln;
	std::cout << "------------\n";

	mat0.print_matrix();

	//  nd::linalg::transpose<T>(nd::matrix<T> mat, axes = {...})
	nd::matrix<int> result0 = nd::linalg::transpose<int>(mat0, { 1, 0 });

	std::cout << "\n=========== transposed ==============\n";

	std::cout << "shape :" << result0.shape() << ", " << result0.own_data()
			<< ln;
	std::cout << "------------\n";

	result0.print_matrix();

	std::cout << "\n============== (3, 2, 2, 2) ================\n";

	shape_t shape = { 3, 2, 2, 2 };
	nd::matrix<int> mat = nd::random::uniform<int>(0, 5, shape);

	mat.data.rprint_vec1d(0, mat.size());

	std::cout << "\n============ transposed =============\n";

	//  nd::linalg::transpose<T>(nd::matrix<T> mat, axes = {...})
	nd::matrix<int> result = nd::linalg::transpose<int>(mat, { 3, 0, 1, 2 });

	result.data.rprint_vec1d(0, result.size());

	std::cout << "\n=================================\n";

}
