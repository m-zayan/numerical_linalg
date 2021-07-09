///*
// * core_iterator.cpp
// *
// *      Author: Z. Mohamed
// */
//
//#include "../../src/iterators/CIterator.hpp"
//
//#define ln '\n'
//
//int main() {
//
//	coords attr0( { 3, 2 }, true, IteratorType::None);
//	coords attr1( { 3, 3, 2 }, true, IteratorType::None);
//
//	CIterator iter( { &attr0, &attr1 });
//
//	iter.op_primitive_alignment("it-test, ");
//
//	std::cout << iter.root_coords().shape << ln;
//
//	for (big_size_t i = 0; i < iter.niter(); i++) {
//
//		std::cout << iter.index1d_ref[0] << ", " << iter.index1d_ref[1] << " | "
//				<< iter.index1d_ref[2] << ln;
//
//		iter._it_next();
//	}
//}
//
