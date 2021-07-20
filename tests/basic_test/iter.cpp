///*
// * iter.cpp
// *
// *      Author: Z. Mohamed
// */
//
//#include "../../src/iterators/factory.hpp"
//
//#include <chrono>
//
//#define ln '\n'
//
//void test0() {
//
//	shape_t s0 = { 2, 3, 3 };
//
//	coords attr0(s0);
//
//	nd::iterator::Iterator *it = new nd::iterator::Iterator(attr0);
//
//	for (big_size_t i = 0; i < it->niter; i++) {
//
//		std::cout << it->index1d << ln;
//
//		ITER_NEXT(it);
//	}
//
//	delete it;
//}
//
//void test1() {
//
//	shape_t s0 = { 3, 3, 2 };
//	shape_t s1 = { 3, 2 };
//
//	coords attr0(s0), attr1(s1);
//
//	nd::iterator::Iterator *it0 = new nd::iterator::Iterator(attr0);
//	nd::iterator::Iterator *it1 = new nd::iterator::Iterator(attr1);
//
//	big_size_t niter = std::max(it0->niter, it1->niter);
//
//	for (big_size_t i = 0; i < niter; i++) {
//
//		std::cout << it0->index1d << ", " << it1->index1d << ln;
//
//		ITER_NEXT(it0);
//		ITER_NEXT(it1);
//	}
//
//	delete it0;
//	delete it1;
//}
//
//void test2() {
//
//	shape_t s0 = { 3, 3, 2 };
//	shape_t s1 = { 3, 1, 2 };
//
//	coords attr0(s0, true, IteratorType::Linear), attr1(s1, false,
//			IteratorType::Linear);
//
//	attr0 = nd::align_dim(attr0, attr1, "iter-test");
//
//	nd::iterator::Iterator *it0 = new nd::iterator::Iterator(attr0);
//	nd::iterator::Iterator *it1 = new nd::iterator::Iterator(attr1);
//
//	big_size_t niter = std::max(it0->niter, it1->niter);
//
//	for (big_size_t i = 0; i < niter; i++) {
//
//		std::cout << it0->default_current << ", " << it1->default_current
//				<< " | " << it0->index1d << ", " << it1->index1d << ln;
//
//		ITER_PAIRWISE2_NEXT(it0, it1);
//	}
//
//	delete it0;
//	delete it1;
//}
//
//void test3() {
//
//	shape_t s0 = { 1000000, 2, 3, 3 };
//	shape_t s1 = { 1000000, 2, 3, 3 };
//
//	coords attr0(s0), attr1(s1);
//
//	nd::iterator::Iterator *it0 = new nd::iterator::Iterator(attr0);
//	nd::iterator::Iterator *it1 = new nd::iterator::Iterator(attr1);
//
//	big_size_t niter = std::max(it0->niter, it1->niter);
//
//	std::cout << "start\n";
//
//	auto t_start = std::chrono::high_resolution_clock::now();
//
//	// about | O3: 39 ms
//	for (big_size_t i = 0; i < niter; i++) {
//
//		ITER_PAIRWISE2_NEXT(it0, it1);
//	}
//
//	auto t_end = std::chrono::high_resolution_clock::now();
//
//	long double time = std::chrono::duration_cast<std::chrono::milliseconds>(
//			t_end - t_start).count();
//
//	std::cout << "Execution Time = " << time << " ms" << ln;
//	std::cout << "\n---------------\n";
//
//	std::cout << "end\n";
//
//	delete it0;
//	delete it1;
//}
//
//void test4() {
//
//	shape_t s0 = { 1000000, 2, 3, 3 };
//	shape_t s1 = { 2, 3, 3 };
//
//	coords attr0(s0), attr1(s1);
//
//	coords out_attr = nd::align_dim(attr0, attr1, "iter-test");
//
//	nd::iterator::Iterator *out_it = new nd::iterator::Iterator(out_attr);
//	nd::iterator::Iterator *it0 = new nd::iterator::Iterator(attr0);
//	nd::iterator::Iterator *it1 = new nd::iterator::Iterator(attr1);
//
//	big_size_t niter = std::max(it0->niter, it1->niter);
//
//	std::cout << "start\n";
//
//	auto t_start = std::chrono::high_resolution_clock::now();
//
//	// about| O0: 552 ms | O3: 180 ms
//	for (big_size_t i = 0; i < niter; i++) {
//
//		ITER_PAIRWISE3_NEXT(out_it, it0, it1);
//	}
//
//	auto t_end = std::chrono::high_resolution_clock::now();
//
//	long double time = std::chrono::duration_cast<std::chrono::milliseconds>(
//			t_end - t_start).count();
//
//	std::cout << "Execution Time = " << time << " ms" << ln;
//	std::cout << "\n---------------\n";
//
//	std::cout << "end\n";
//
//	delete it0;
//	delete it1;
//	delete out_it;
//}
//
//void test5() {
//
//	shape_t shape = { 5, 4, 6, 3 };
//
//	coords attr(shape);
//
//	nd::iterator::Iterator *it = nd::iterator::init_2d_iterator(attr);
//
//	std::cout << it->default_shape << '\n';
//
//	DI3_MOVE_ALONG(it, -2);
//
//	max_size_t chunk_size = DI3_NITER2(it);
//	max_size_t n_chunk = DI3_NITER3(it);
//
//	for (max_size_t i = 0; i < n_chunk; i++) {
//
//		for (max_size_t j = 0; j < chunk_size; j++) {
//
//			std::cout << it->index1d << ln;
//
//			DI3_NEXT(it);
//		}
//
//		std::cout << "----------\n";
//	}
//
//	nd::iterator::free_iterator(it);
//}
//
//void test6() {
//
//	shape_t shape = { 1000, 900, 800, 700 };
//
//	coords attr(shape);
//
//	nd::iterator::Iterator *it = nd::iterator::init_2d_iterator(attr);
//
//	std::cout << it->default_shape << '\n';
//
//	DI3_MOVE_ALONG(it, -2);
//
//	max_size_t chunk_size = DI3_NITER2(it);
//	max_size_t n_chunk = DI3_NITER3(it);
//
//	std::cout << "n-iter :" << (chunk_size * n_chunk) / 1e6 << " M" << ln;
//
//	std::cout << "start\n";
//
//	auto t_start = std::chrono::high_resolution_clock::now();
//
//	// about| O0: 5418 ms | O3: 1456 ms
//	for (max_size_t i = 0; i < n_chunk; i++) {
//
//		for (max_size_t i = 0; i < chunk_size; i++) {
//
//			DI3_NEXT(it);
//		}
//	}
//
//	auto t_end = std::chrono::high_resolution_clock::now();
//
//	long double time = std::chrono::duration_cast<std::chrono::milliseconds>(
//			t_end - t_start).count();
//
//	std::cout << "Execution Time = " << time << " ms" << ln;
//	std::cout << "\n---------------\n";
//
//	std::cout << "end\n";
//
//	nd::iterator::free_iterator(it);
//}
//
//int main() {
//
//	test6();
//}
