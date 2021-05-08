///*
// * nd_pairwise_iter.cpp
// *
// *	Author: Z. Mohamed
// */
//
//#include "../src/iterators/Pairwise.hpp"
//
//#define ln '\n'
//
//int main() {
//
//	shape_t shape1 = { 3, 1, 2, 4 }; // {3, 3, 2, 4} error
//	shape_t shape2 = { 2, 1, 4 };
//
//	coords attr1 = coords(shape1);
//	coords attr2 = coords(shape2);
//
//	nd::iterator::Pairwise iter(attr1, attr2);
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
//
//	for (big_size_t i = 0; i < size; i++) {
//		std::cout << iter.indices_at(i, 0) << ", " << iter.indices_at(i, 1)
//		<< ln;
//	}
//
////	for (big_size_t i = 0; i < size; i++) {
////		std::cout << iter.index_at(i, 0) << ", " << iter.index_at(i, 1) << ln;
////	}
//}
