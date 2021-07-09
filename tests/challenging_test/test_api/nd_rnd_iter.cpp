/*
 * nd_rnd_iter.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./test_api.hpp"

#include "../../../src/deprecated/iterators/Pairwise.hpp"

void test_api::nd_rnd_iter() {

	shape_t s0 = { 1000000, 2, 3, 3 };
	shape_t s1 = { 2, 3, 3 };

	coords attr0(s0), attr1(s1);

	nd::iterator::Pairwise pIter(attr0, attr1);

	big_size_t size = pIter.aligned_coords(2).size1d;

	std::cout << "start\n";

	auto t_start = std::chrono::high_resolution_clock::now();

	// about - O0:  ms | O3 :  ms
	for (big_size_t i = 0; i < size; i++) {

		if ((pIter.index_at(i, 0) && pIter.index_at(i, 1))
				&& pIter.index_at(i, 2)) {
			continue;
		}
	}

	auto t_end = std::chrono::high_resolution_clock::now();

	long double time = std::chrono::duration_cast<std::chrono::milliseconds>(
			t_end - t_start).count();

	std::cout << "Execution Time = " << time << " ms" << ln;
	std::cout << "\n-----------------\n";

	std::cout << "end\n";
}

