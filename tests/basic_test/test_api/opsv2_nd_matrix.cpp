/*
 * opsv2_nd_matrix.cpp
 *
 *      Author: Z. Mohamed
 */

#include "test_api.hpp"

void test_concat() {

	shape_t s0 = { 3, 3 };
	nd::matrix<int> m0 = nd::random::uniform<int>(-5, 5, s0);

	nd::out::print_matrix(m0);

	std::cout << "\n==========================\n";

	shape_t s1 = { 3, 3 };
	nd::matrix<int> m1 = nd::linalg::eye<int>(s1);

	nd::out::print_matrix(m1);

	std::cout << "\n==========================\n";

	nd::matrix<int> res = nd::concat<int>( { m0, m1 }, 0);

	nd::out::print_matrix(res.permute( { 1, 0 }));

}

void test_aug() {

	shape_t s = { 3, 3 };

	nd::matrix<int> mat = nd::random::uniform<int>(1, 10, s);

	nd::out::print_matrix(mat);

	std::cout << "\n==========================\n";

	nd::matrix<double> aug = nd::linalg::augmented<double>(mat);

	nd::out::print_matrix(aug[0]);

	std::cout << "\n---------------------\n";

	std::cout << aug[0].shape() << '\n';

	std::cout << "\n==========================\n";

	nd::matrix<double, false> slice0 = aug[0].slice( { 0, 3 }, { });

	nd::out::print_matrix(slice0);

	std::cout << "\n---------------------\n";

	std::cout << slice0.shape() << '\n';

	std::cout << "\n==========================\n";

	nd::matrix<double, false> slice1 = aug[0].slice( { }, { 3, 3 });

	nd::out::print_matrix(slice1);

	std::cout << "\n---------------------\n";

	std::cout << slice1.shape() << '\n';

	std::cout << "\n==========================\n";

	nd::matrix<double, false> slice2 = aug[0].permute( { 1, 0 }).slice( { }, {
			3, 3 });

	nd::out::print_matrix(slice2);

	std::cout << "\n---------------------\n";

	std::cout << slice2.shape() << '\n';
}

void test_slice(shape_t shape, shape_t begin, shape_t end) {

	nd::matrix<int> mat = nd::random::uniform<int>(1, 10, shape);

	nd::out::print_matrix(mat);

	std::cout << "\n==========================\n";

	nd::matrix<int, false> slice = mat.slice(begin, end);

	std::cout << "shape :" << slice.shape() << ", " << "strides :"
			<< shape_t(slice.strides()) << '\n';

	std::cout << "\n---------------------\n";

	nd::out::print_matrix(slice);

}

void test_eye(shape_t shape, max_t dshift) {

	nd::matrix<int> mat = nd::linalg::eye<int>(shape, dshift);

	std::cout << "shape :" << mat.shape() << ", " << "strides :"
			<< shape_t(mat.strides()) << '\n';

	std::cout << "\n---------------------\n";

	nd::out::print_matrix(mat);

	std::cout << "\n==========================\n";
}

void test_api::opsv2_nd_matrix() {

	for (max_t i = -3; i <= 3; i++) {
		test_eye( { 3, 4 }, i);
	}
}
