///*
// * test_vec1d.cpp
// *
// *	Author: Z. Mohamed
// */
//
//#include <iostream>
//#include "../src/common/vec1d.cpp"
//
//#define ln '\n'
//
//int main() {
//
//	vec1d<int> a = { 1, 2, 3, 4 };
//
//	((a * a) - (a + a) / 2 + 1).print_vec1d(0, a.size());
//	std::cout << "\n===========\n";
//
//	vec1d<std::shared_ptr<int>> b(a.size());
//
//	for (max_size_t i = 0; i < b.size(); i++) {
//
//		b[i] = allocator::val_to_shared_ptr(5);
//	}
//
//	vec1d<weak_ptr<int>> c(a.size());
//
//	for (max_size_t i = 0; i < c.size(); i++) {
//
//		c[i] = b[i];
//	}
//
//	for (max_size_t i = 0; i < c.size(); i++) {
//
//		std::cout << c[i].get() << ln;
//	}
//}
//
