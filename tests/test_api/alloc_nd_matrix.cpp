/*
 * alloc_nd_matrix.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::alloc_nd_matrix() {

	shape_t shape = { 3, 3, 3 };

	nd::matrix<int> mat = nd::random::uniform<int>(1, 3, shape); // low = 1, high = 3

	std::cout << "shape :" << mat.shape() << ln;
	std::cout << "Chunk storage size :" << mat.size() << ln;

	std::cout << "=======================\n";
	nd::out::print_matrix(mat);

	std::cout << "\n========== matrix[0] ============\n";
	nd::out::print_matrix(mat[0]);

	std::cout << "========== matrix[0][1] ============\n";
	nd::out::print_matrix(mat[0][1]);

	std::cout << "\n========== matrix[1] ============\n";
	nd::out::print_matrix(mat[1]);

	std::cout << "========== matrix[1][2] ============\n";
	nd::out::print_matrix(mat[1][2]);

	std::cout << "\n========== matrix[2] ============\n";
	nd::out::print_matrix(mat[2]);

	std::cout << "========== matrix[2][3] ============\n";
	nd::out::print_matrix(mat[2][2]);

	std::cout << "\n========== Updated: op: diag(matrix) = 0 ============\n";

	for (max_size_t i = 0; i < 3; i++) {
		for (max_size_t j = 0; j < 3; j++) {
			mat.assign( { i, j, j }, 0);
		}
	}

	nd::out::print_matrix(mat);

	std::cout << "\n============ op: div =========\n";

	mat /= 1;
	nd::out::print_matrix(mat / 2);

	std::cout << "\n============ op: mul =========\n";

	mat *= 2;
	nd::out::print_matrix(mat * mat * 2);

	std::cout << "\n============ op: sub =========\n";

	mat /= 2;
	nd::out::print_matrix(mat - 2);

	std::cout << "\n============ op: add =========\n";

	nd::out::print_matrix(mat + 2);

	std::cout << "\n============ op: equal =========\n";

	std::cout << (mat == mat) << ", " << (mat == (mat + 1)) << '\n';

	std::cout << "\n============ op: mask =========\n";

	nd::out::print_matrix(mat == 2);

	std::cout << "\n========== [1]: Identity - {3, 3} =======\n";

	shape_t shape0 = { 3, 3 };
	nd::matrix<int> mat0 = nd::linalg::eye<int>(shape0);

	nd::out::print_matrix(mat0);

	std::cout << "\n========== [2]: Diag(matrix) = 3 - {3, 3} =======\n";

	shape_t shape1 = { 3, 3 };
	nd::matrix<int> mat1 = nd::linalg::eye<int>(shape1);

	mat1 *= 3;

	nd::out::print_matrix(mat1);

	std::cout << "\n========== Stack [1], [2] =======\n";

	nd::matrix<int> result = nd::stack<int>( { mat0, mat1 });

	nd::out::print_matrix(result);
}
