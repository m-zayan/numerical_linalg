/*
 * linalg_transpose.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::linalg_transpose() {

	shape_t shape0 = { 3, 2 };
	nd::matrix<int> mat0 = nd::random::uniform<int>(0, 5, shape0);

	std::cout << "shape :" << mat0.shape() << ", own_data: " << mat0.own_data()
			<< ln;
	std::cout << "------------\n";

	mat0.print_matrix();

	//  nd::linalg::transpose<T>(nd::matrix<T> mat, axes = {...})
	nd::matrix<int> result0 = nd::linalg::transpose<int>(mat0, { 1, 0 });

	std::cout << "\n\n=========== transposed, axes = {1, 0} ==============\n";

	std::cout << "shape :" << result0.shape() << ", own_data: "
			<< result0.own_data() << ln;

	std::cout << "\n------------\n";

	result0.print_matrix();

	std::cout << "\n\n==============================\n";

	shape_t shape = { 3, 2, 2, 2 };
	nd::matrix<int> mat = nd::random::uniform<int>(0, 5, shape);

	std::cout << "shape :" << mat.shape() << ", own_data :" << mat.own_data()
			<< ln;
	std::cout << "\n------------\n";
	std::cout << "data : ";
	mat.data.rprint_vec1d(0, mat.size());

	std::cout
			<< "\n\n============ transposed, axes = { 3, 0, 1, 2 } =============\n";

	nd::matrix<int> result = nd::linalg::transpose<int>(mat, { 3, 0, 1, 2 });

	std::cout << "shape :" << result.shape() << ", own_data :"
			<< result.own_data() << ln;
	std::cout << "\n------------\n";
	std::cout << "data : ";

	result.data.rprint_vec1d(0, result.size());

	std::cout << "\n=================================\n";

}
