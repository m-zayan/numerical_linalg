///*
// * test_reindex.cpp
// *
// *	Author: Z. Mohamed
// */
//
//#include <iostream>
//#include "../src/deprecated/iterators/RandomAccess.hpp"
//
//#define ln '\n'
//
//big_size_t validate(big_size_t index_1d, nd::iterator::RandomAccess rndIter,
//		big_size_t size) {
//
//	for (big_size_t i = 0; i < size; i++) {
//		if (rndIter.index_at(i) == index_1d)
//			return i;
//	}
//
//	return -1; // 0xfffff...
//}
//int main() {
//
//	shape_t shape = { 5, 3, 4, 2, 5, 6, 1 };
//	coords attr(shape);
//
//	shape_t axes = { 0, 3, 1, 6, 5, 4, 2 };
//	coords pattr = attr.permuted(axes, false);
//
//	nd::iterator::RandomAccess rndIter(pattr);
//
//	for (big_size_t i = 0; i < attr.size1d; i++) {
//		if (validate(i, rndIter, attr.size1d) != rndIter.reversed_index_at(i))
//			std::cout << "invalid at i = : " << i << ln;
//	}
//
//	std::cout << "done\n";
//}
