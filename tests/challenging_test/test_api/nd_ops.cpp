/*
 * nd_ops.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_add() {

	shape_t s0 = { 1000000, 2, 3, 3 };
	shape_t s1 = { 2, 3, 3 };

	nd::matrix<double> m0 = nd::random::uniform(0.0, 1.0, s0);
	nd::matrix<double> m1 = nd::random::uniform(0.0, 1.0, s1);

	std::cout << "start\n";

	auto t_start = std::chrono::high_resolution_clock::now();

	// about |  O3 : 274 ms
	nd::matrix<double> out = m0 + m1;

	auto t_end = std::chrono::high_resolution_clock::now();

	long double time = std::chrono::duration_cast<std::chrono::milliseconds>(
			t_end - t_start).count();

	std::cout << "Execution Time = " << time << " ms" << ln;
	std::cout << "\n=============================================\n";
	std::cout << out.shape() << '\n';

	std::cout << "end\n";
}

void test_inv() {

	shape_t shape = { 1000000, 2, 3, 3 };

	nd::matrix<double> mat = nd::random::uniform(1, 1000000, shape);

	std::cout << "start\n";

	auto t_start = std::chrono::high_resolution_clock::now();

	// about | O0: 24 s |  O3 : 2681 ms
	nd::matrix<double> inv = nd::linalg::inverse(mat);

	auto t_end = std::chrono::high_resolution_clock::now();

	long double time = std::chrono::duration_cast<std::chrono::milliseconds>(
			t_end - t_start).count();

	std::cout << "Execution Time = " << time << " ms" << ln;
	std::cout << "\n=============================================\n";
	std::cout << inv.shape() << '\n';

	std::cout << "end\n";
}

void test_api::nd_ops() {

	test_inv();
}
