///*
// * nd_pairwise_seq_iter.cpp
// *
// *      Author: Z. Mohamed
// */
//
//#include "../../src/deprecated/iterators/Pairwise.hpp"
//#include "../../src/deprecated/iterators/PairwiseSequential.hpp"
//
//#define ln '\n'
//
//void test_0() {
//
//	shape_t shape1 = { 3, 1, 2, 4 }; // {3, 3, 2, 4} error
//	shape_t shape2 = { 2, 1, 4 };
//
//	coords attr1 = coords(shape1);
//	coords attr2 = coords(shape2);
//
//	nd::iterator::PairwiseSequential iter(attr1, attr2);
//
//	std::cout << "axes 0 : " << iter.aligned_coords(0).axes << ln;
//	std::cout << "axes 1 : " << iter.aligned_coords(1).axes << ln;
//	std::cout << "axes 2 : " << iter.aligned_coords(2).axes << ln;
//
//	std::cout << "shape 0 : " << iter.aligned_coords(0).shape << ln;
//	std::cout << "shape 1 : " << iter.aligned_coords(1).shape << ln;
//	std::cout << "shape 2 : " << iter.aligned_coords(2).shape << ln;
//
//	big_size_t size = iter.aligned_coords(2).size1d;
//	big_size_t i = 0;
//
//	std::cout << "size :" << size << ln;
//
//	while (iter.next()) {
//
//		std::cout << iter.indices(0) << ", " << iter.indices(1) << ln;
//
//		i++;
//
//	}
//
//	std::cout << "steps :" << i << ln;
//}
//
//void test_1() {
//
//	shape_t shape1 = { 1000, 3, 1, 2, 5 };
//	shape_t shape2 = { 3, 2, 5 };
//
//	coords attr1 = coords(shape1);
//	coords attr2 = coords(shape2);
//
//	nd::iterator::PairwiseSequential iter(attr1, attr2);
//	nd::iterator::Pairwise iter2(attr1, attr2);
//
//	big_size_t i = 1;
//
//	while (iter.next()) {
//
//		for (min_size_t j = 0; j < 3; j++) {
//
//			if (iter2.indices_at(i, j) != iter.indices(j)) {
//				std::cout << "pair :" << j << ln;
//				std::cout << iter.indices(j) << ", " << iter2.indices_at(i, j)
//						<< ln;
//
//				std::cout << "\nInvalid\n";
//
//				return;
//			}
//		}
//
//		i++;
//
//	}
//
//	std::cout << "Done\n";
//
//}
//
//void test_2() {
//
//	shape_t shape1 = { 1000, 3, 1, 2, 5 };
//	shape_t shape2 = { 3, 2, 5 };
//
//	coords attr1 = coords(shape1);
//	coords attr2 = coords(shape2);
//
//	nd::iterator::PairwiseSequential iter(attr1, attr2);
//	nd::iterator::Pairwise iter2(attr1, attr2);
//
//	big_size_t i = 1;
//
//	while (iter.next()) {
//
//		for (min_size_t j = 0; j < 3; j++) {
//
//			if (iter2.index_at(i, j) != iter.index(j)) {
//				std::cout << "pair :" << j << ln;
//				std::cout << iter.index(j) << ", " << iter2.index_at(i, j)
//						<< ln;
//
//				std::cout << "\nInvalid\n";
//
//				return;
//			}
//		}
//
//		i++;
//
//	}
//
//	std::cout << "Done\n";
//
//}
//int main() {
//
//	test_2();
//}
//
