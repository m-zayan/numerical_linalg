///*
// * nd_iter_factory.cpp
// *
// *      Author: Z. Mohamed
// */
//
//#include "../../src/multidim/ufunc.hpp"
//
//#define ln '\n'
//
//int main() {
//
//	shape_t shape = { 3, 3 };
//
//	coords attr(shape, true, IteratorType::None);
////	attr = attr.permuted( { 1, 0 }, false);
//
//	nd::iterator::Iterator *iter = nd::iterator::init_iterator(attr);
//
//	std::cout << attr.size1d << '\n';
//
//	do {
//		std::cout << iter->index() << ln;
//	} while (iter->next());
//
//	nd::iterator::free_iterator(iter);
//
//}
//
