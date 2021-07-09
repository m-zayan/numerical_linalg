/*
 * iter.cpp
 *
 *      Author: Z. Mohamed
 */

#include "../../../src/iterators/Iterator.hpp"

#include <chrono>

#define ln '\n'

void test0() {
	shape_t s0 = { 2, 3, 3 };

	coords attr0(s0);

	nd::iterator::Iterator *it = new nd::iterator::Iterator(attr0);

	for (big_size_t i = 0; i < it->niter; i++) {

		std::cout << it->index1d << ln;

		ITER_NEXT(it);
	}

	delete it;
}

void test1() {

	shape_t s0 = { 3, 3, 2 };
	shape_t s1 = { 3, 2 };

	coords attr0(s0), attr1(s1);

	nd::iterator::Iterator *it0 = new nd::iterator::Iterator(attr0);
	nd::iterator::Iterator *it1 = new nd::iterator::Iterator(attr1);

	big_size_t niter = std::max(it0->niter, it1->niter);

	for (big_size_t i = 0; i < niter; i++) {

		std::cout << it0->index1d << ", " << it1->index1d << ln;

		ITER_NEXT(it0);
		ITER_NEXT(it1);
	}

	delete it0;
	delete it1;
}

void test2() {

	shape_t s0 = { 1000000, 2, 3, 3 };
	shape_t s1 = { 2, 3, 3 };

	coords attr0(s0), attr1(s1);

	nd::iterator::Iterator *it0 = new nd::iterator::Iterator(attr0);
	nd::iterator::Iterator *it1 = new nd::iterator::Iterator(attr1);

	big_size_t niter = std::max(it0->niter, it1->niter);

	std::cout << "start\n";

	auto t_start = std::chrono::high_resolution_clock::now();

	for (big_size_t i = 0; i < niter; i++) {

		ITER_NEXT(it0);
		ITER_NEXT(it1);
	}

	auto t_end = std::chrono::high_resolution_clock::now();

	long double time = std::chrono::duration_cast<std::chrono::milliseconds>(
			t_end - t_start).count();

	std::cout << "Execution Time = " << time << " ms" << ln
	;
	std::cout << "\n---------------\n";

	std::cout << "end\n";

	delete it0;
	delete it1;
}

void test3() {

	shape_t s0 = { 3, 3, 2 };
	shape_t s1 = { 3, 2 };

	coords attr0(s0, true, IteratorType::Linear), attr1(s1, false,
			IteratorType::Linear);

	nd::iterator::Iterator *it0 = new nd::iterator::Iterator(attr0);
	nd::iterator::Iterator *it1 = new nd::iterator::Iterator(attr1);

	big_size_t niter = std::max(it0->niter, it1->niter);

	for (big_size_t i = 0; i < niter; i++) {

		std::cout << it0->current << ", " << it1->current << ln;

		ITER_NEXT(it0);
		ITER_NEXT(it1);
	}

	delete it0;
	delete it1;
}

int main() {

	test3();

}
