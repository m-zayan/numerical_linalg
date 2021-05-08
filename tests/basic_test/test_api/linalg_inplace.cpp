///*
// * linalg_inplace.cpp
// *
// *	Author: Z. Mohamed
// */
//
//#include "./test_api.hpp"
//
//void test_api::linalg_inplace() {
//
//	shape_t shape0 = { 3, 2 };
//	nd::matrix<int> mat0 = nd::random::uniform<int>(0, 5, shape0);
//
//	std::cout << "shape :" << mat0.shape() << ", own_data: " << mat0.own_data()
//			<< ln;
//	std::cout << "------------\n";
//
//	nd::out::print_matrix(mat0);
//
//	std::cout << "\n==============================\n";
//
//	//  nd::linalg::transpose<T>(nd::matrix<T> mat, axes = {...})
//	nd::linalg::inplace::transpose<int>(mat0, { 1, 0 });
//
//	nd::out::_h::print_vec1d(mat0._m_begin(), 0, mat0.size());
//
//	std::cout << "\n\n==============================\n";
//
//	shape_t shape = { 3, 2, 2, 2 };
//
//	nd::matrix<int> mat = nd::random::uniform<int>(0, 5, shape);
//
//	std::cout << "shape :" << mat.shape() << ", own_data :" << mat.own_data()
//			<< ln;
//
//	std::cout << "\n------------\n";
//	std::cout << "data : ";
//
//	nd::out::_h::print_vec1d(mat._m_begin(), 0, mat.size());
//
//	std::cout
//			<< "\n\n============ transposed, axes = { 3, 0, 1, 2 } =============\n";
//
//	nd::linalg::inplace::transpose<int>(mat, { 3, 0, 1, 2 });
//
//	std::cout << "shape :" << mat.shape() << ", own_data :" << mat.own_data()
//			<< ln;
//
//	std::cout << "\n------------\n";
//	std::cout << "data : ";
//
//	nd::out::_h::print_vec1d(mat._m_begin(), 0, mat.size());
//
//	std::cout << "\n=================================\n";
//
//}
