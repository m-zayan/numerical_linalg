///*
// * test_vec1d.cpp
// *
// *	Author: Z. Mohamed
// */
//#include <iostream>
//#include "../src/typing/utypes/types.hpp"
//
//#define ln '\n'
//
////template<typename T, T ...Bounds>
////class const_bounded_t: public bounded_t<T> {
////
////public:
////
////	using bounded_t<T>::bounds;
////
////
////	const_bounded_t(std::string sig, T val) :
////			bounded_t<T>::bounded_t( { }, sig, val) {
////	}
////
////};
//
//int main() {
//
////	vec1d<int> a = { 1, 2, 3, 4 };
////
////	((a * a) - (a + a) / 2 + 1).print_vec1d(0, a.size());
////	std::cout << "\n===========\n";
////
////	vec1d<std::shared_ptr<int>> b(a.size());
////
////	for (max_size_t i = 0; i < b.size(); i++) {
////
////		b[i] = allocator::val_to_shared_ptr(5);
////	}
////
////	vec1d<weak_ptr<int>> c(a.size());
////
////	for (max_size_t i = 0; i < c.size(); i++) {
////
////		c[i] = b[i];
////	}
////
////	for (max_size_t i = 0; i < c.size(); i++) {
////
////		std::cout << c[i].get() << ln;
////	}
//
//	bounded_t<min_size_t> bndt( { 0, 1, 2 }, "EnableX", 2);
//
//	std::cout << bndt << ln;
//
//	max_size_t bs = std::min(static_cast<max_size_t>(1),
//			static_cast<max_size_t>(bndt));
//	std::cout << bs << ln;
//
////	bndt = 3; // error
//
//	bounded_initializer<min_size_t, 0, 1, 3> bnd("II", 3);
//	std::cout << bnd << ln;
//
////	bounded_initializer<min_size_t, 0, 1, 2> ex("EnableX", 3); // error
//
//}
