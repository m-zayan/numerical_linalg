/*
 * alloc_nd_matrix.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::alloc_nd_matrix() {

	shape_t shape = { 3, 3 };

	nd::matrix<int> mat = nd::random::uniform<int>(1, 10, shape); // low = 1, high = 10

	std::cout << "shape :" << mat.shape() << ln;
	std::cout << "Chunk storage size :" << mat.size() << ln;

	std::cout << "=======================\n";
	mat.print_matrix();

	std::cout << "========== matrix[0] ============\n";
	mat[0].print_matrix();

	std::cout << "========== matrix[1] ============\n";
	mat[1].print_matrix();

	std::cout << "========== matrix[2] ============\n";
	mat[2].print_matrix();

	std::cout << "========== Updated: op: diag(matrix) = 0 ============\n";

	for (max_size_t i = 0; i < 3; i++) {
		mat.assign( { i, i }, 0);
	}

	mat.print_matrix();

	std::cout
			<< "============ op: (matrix * matrix) - (matrix + matrix) =========\n";
	((mat * mat) - (mat + mat)).print_matrix();

	std::cout << "============ Matrix (3, 3, 2)==========\n";

	shape_t shape2 = { 3, 3, 2 };

	nd::matrix<int> mat2 = nd::random::uniform<int>(1, 10, shape2); // low = 1, high = 10
	mat2.print_matrix();

	std::cout << "----------------\n";

	std::cout << std::boolalpha;
	std::cout << "mat2 - own-data :" << mat2.own_data() << ln;
	std::cout << "mat2[0] - own-data :" << mat2[0].own_data() << ln;

	std::cout << "========== [1]: Identity - {3, 3} =======\n";

	shape_t shape_01 = { 3, 3 };
	nd::matrix<int> mat_01 = nd::linalg::eye<int>(shape_01);

	mat_01.print_matrix();

	std::cout << "========== [2]: Diag(matrix) = 3 - {3, 3} =======\n";

	shape_t shape_02 = { 3, 3 };
	nd::matrix<int> mat_02 = nd::linalg::eye<int>(shape_02);

	mat_02 *= 3;
	mat_02.print_matrix();

	std::cout << "========== Stack [1], [2] =======\n";

	nd::matrix<int> result = nd::stack<int>( { mat_01, mat_02 });

	result.print_matrix();
}
