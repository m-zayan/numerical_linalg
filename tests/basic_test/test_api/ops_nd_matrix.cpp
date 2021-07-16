/*
 * ops_nd_matrix.cpp
 *
 *	Author: Z. Mohamed
 */

#include "test_api.hpp"

template<typename T>
void test_min(nd::matrix<T> mat, max_size_t axis = 0) {

	nd::matrix<T> result = nd::numeric::min<int>(mat, axis);

	std::cout << " shape : " << result.shape() << "\n -------------- \n";

	nd::out::print_matrix(result);

	std::cout << "\n ============================= \n";
}

template<typename T>
void test_argmin(nd::matrix<T> mat, max_size_t axis = 0) {

	nd::matrix<T> result = nd::numeric::argmin<T>(mat, axis);

	std::cout << " shape : " << result.shape() << "\n -------------- \n";

	nd::out::print_matrix(result);

	std::cout << "\n ============================= \n";
}

template<typename T>
void test_max(nd::matrix<T> mat, max_size_t axis = 0) {

	nd::matrix<T> result = nd::numeric::max<T>(mat, axis);

	std::cout << " shape : " << result.shape() << "\n -------------- \n";

	nd::out::print_matrix(result);

	std::cout << "\n ============================= \n";
}

template<typename T>
void test_argmax(nd::matrix<T> mat, max_size_t axis = 0) {

	nd::matrix<T> result = nd::numeric::argmax<T>(mat, axis);

	std::cout << " shape : " << result.shape() << "\n -------------- \n";

	nd::out::print_matrix(result);

	std::cout << "\n ============================= \n";
}

template<typename T>
void test_sum(nd::matrix<T> mat, max_size_t axis = 0) {

	nd::matrix<T> result = nd::numeric::sum<T>(mat, axis);

	std::cout << " shape : " << result.shape() << "\n -------------- \n";

	nd::out::print_matrix(result);

	std::cout << "\n ============================= \n";
}

template<typename T>
void test_mean(nd::matrix<T> mat, max_size_t axis = 0) {

	nd::matrix<double> result = nd::numeric::mean<double>(mat, axis);

	std::cout << " shape : " << result.shape() << "\n -------------- \n";

	nd::out::print_matrix(result);

	std::cout << "\n ============================= \n";
}

template<typename T>
void test_var(nd::matrix<T> mat, max_size_t axis = 0) {

	nd::matrix<double> result = nd::numeric::var<double>(mat, axis);

	std::cout << " shape : " << result.shape() << "\n -------------- \n";

	nd::out::print_matrix(result);

	std::cout << "\n ============================= \n";
}

template<typename T>
void test_std(nd::matrix<T> mat, max_size_t axis = 0) {

	nd::matrix<double> result = nd::numeric::std<double>(mat, axis);

	std::cout << " shape : " << result.shape() << "\n -------------- \n";

	nd::out::print_matrix(result);

	std::cout << "\n ============================= \n";
}

void test_api::ops_nd_matrix() {

	shape_t s = { 20, 20 };
	nd::matrix<int> mat = nd::random::uniform(0, 10, s);

	nd::out::_h::print_vec1d(mat._m_begin(), 0, mat.size());

	std::cout << "\n ============================= \n";

//	test_min(mat);
//	test_argmin(mat);

//	test_max(mat);
//	test_argmax(mat);

//	test_sum(mat);
//	test_mean(mat);

	// pairwise
	nd::mem::AUX_SIZE = 2;

	test_var(mat);
	test_std(mat);
}
