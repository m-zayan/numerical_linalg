/*
 * nd_seq_iter.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test_api::nd_seq_iter() {

	shape_t s0 = { 1000000, 2, 3, 3 };
	shape_t s1 = { 2, 3, 3 };

	coords attr0(s0), attr1(s1);

	nd::iterator::PairwiseSequential pIter(attr0, attr1);

	std::cout << "start\n";

	auto t_start = std::chrono::high_resolution_clock::now();

	// about - O0:  ms | O3 :  ms
	do {
	} while (pIter.next());

	auto t_end = std::chrono::high_resolution_clock::now();

	long double time = std::chrono::duration_cast<std::chrono::milliseconds>(
			t_end - t_start).count();

	std::cout << "Execution Time = " << time << " ms" << ln;
	std::cout << "\n-----------------\n";

	std::cout << "end\n";
}
