///*
// * reorder_copy.cpp
// *
// *	Author: Z. Mohamed
// */
//
//#include "./test_api.hpp"
//
//void test_api::reorder_copy() {
//
//	shape_t shape0 = { 2, 3, 3 };
//	nd::matrix<int> mat0 = nd::linalg::eye<int>(shape0);
//
//	shape_t shape1 = { 3, 3 };
//	nd::matrix<int> mat1 = nd::random::uniform<int>(0, 10, shape1);
//
//	for (max_size_t i = 0; i < 3; i++) {
//
//		for (max_size_t j = 0; j < 3; j++) {
//
//			shape_t indices = { i, j };
//
//			mat1.at(indices) += (i + j);
//		}
//
//	}
//
//	nd::out::print_matrix(mat0);
//
//	std::cout << "\n ======================= \n";
//
//	nd::out::print_matrix(mat1);
//
//	std::cout << "\n ======================= \n";
//
////	nd::matrix<int> res0 = nd::stack<int>( { mat0[0], mat1 });
////
////	nd::out::print_matrix(res0);
////
////	std::cout << "\n ======================= \n";
////
////	std::cout << "\n own_data : " << mat1.permute( { 1, 0 }).own_data() << ln;
////
////	std::cout << "\n ----------------------- \n";
////
////	nd::matrix<int> res1 = nd::stack<int>(
////			{ mat0[0], mat1.permute( { 1, 0 }) });
////
////	nd::out::print_matrix(res1);
////
////	std::cout << "\n ======================= \n";
//
//	nd::matrix<double> res2 = nd::linalg::matmul<double>(mat0, mat1.permute( {
//			1, 0 })) + 0.5;
//
//	nd::out::print_matrix(res2);
//
//	std::cout << "\n ======================= \n";
//
//}
