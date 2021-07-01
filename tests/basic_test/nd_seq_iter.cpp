///*
// * nd_seq_iter.cpp
// *
// *	Author: Z. Mohamed
// */
//
//#include <iostream>
//#include <memory>
//
//#include "../../src/iterators/Sequential.hpp"
//#include "../../src/iterators/RandomAccess.hpp"
//
//#define ln '\n'
//
//void test_0() {
//
//	shape_t shape = { 4, 3, 2, 2 };
//
//	nd::iterator::Sequential seqIter(shape);
//
//	max_size_t count = 0;
//
//	std::cout << seqIter.indices() << " : " << count++ << ln;
//
//	while (seqIter.next()) {
//
//		std::cout << seqIter.indices() << ", " << seqIter.index() << " : "
//				<< count++ << ln;
//	}
//}
//
//void test_1() {
//
//	shape_t shape = { 10, 23, 100, 100 };
//
//	coords attr(shape);
//
//	attr = attr.permuted( { 2, 0, 1, 3 }, false);
//
//	nd::iterator::Sequential seqIter(attr);
//	nd::iterator::RandomAccess rndIter(attr);
//
//	big_size_t i = 1;
//
//	while (seqIter.next()) {
//
//		if (rndIter.index_at(i) != seqIter.index()) {
//
//			std::cout << rndIter.index_at(i) << ", " << seqIter.index()
//					<< "\nInvalid\n";
//			return;
//		}
//
//		i++;
//
//	}
//
//	std::cout << "Done\n";
//}
//
//void test_3() {
//
//	shape_t shape = { 3, 2, 2 };
//
//	coords attr(shape);
//
//	nd::iterator::Sequential seqIter(attr);
//
//	seqIter.slice( { 2, 1 }, { });
//
//	do {
//
//		std::cout << seqIter.indices() << " : " << seqIter.index() << ln;
//
//	} while (seqIter.next());
//
//}
//
//void test_4() {
//
//	shape_t shape = { 3, 2, 2 };
//
//	coords attr(shape);
//
//	nd::iterator::Sequential seqIter(attr);
//
//	do {
//
//		std::cout << seqIter.indices() << " : " << seqIter.index() << " | " << seqIter.iaxis() << ln;
//
//	} while (seqIter.next());
//
//}
//
//
//int main() {
//	test_4();
//}
