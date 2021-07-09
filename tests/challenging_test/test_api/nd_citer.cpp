/*
 * nd_citer.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::nd_citer() {

	shape_t s0 = { 1000000, 2, 3, 3 };
	shape_t s1 = { 2, 3, 3 };

	coords attr0(s0, true, IteratorType::None);
	coords attr1(s1, true, IteratorType::None);

	CIterator it( { &attr0, &attr1 });

	it.op_primitive_alignment("it-test, ");

	std::cout << it.niter() << ln;

	std::cout << "start\n";

	auto t_start = std::chrono::high_resolution_clock::now();

	// about  O3 :413  ms
	for (big_size_t i = 0; i < it.niter(); i++) {
		it._it_next();
	}

	auto t_end = std::chrono::high_resolution_clock::now();

	long double time = std::chrono::duration_cast<std::chrono::milliseconds>(
			t_end - t_start).count();

	std::cout << "Execution Time = " << time << " ms" << ln;
	std::cout << "\n-----------------\n";

	std::cout << "end\n";
}

