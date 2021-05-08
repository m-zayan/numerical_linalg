///*
// * nd_broadcasting.cpp
// *
// *	Author: Z. Mohamed
// */
//
//#include "test_api.hpp"
//
//void test_api::nd_broadcasting() {
//
//	shape_t s1 = { 3, 1, 3, 2 };
//	shape_t s2 = { 2, 3, 1 };
//
//	std::cout << "broadcastable : " << ((s1 & s2) == 2) << "\n";
//	std::cout << "\n===========================\n";
//
////	nd::state::BroadcastingLevel = 0; // given (s1, s2) - error
////	nd::state::BroadcastingLevel = 1; // given (s1, s2) - error
//
////	nd::state::BroadcastingLevel = 2; // default
//
//	nd::matrix<int> m0 = nd::random::uniform(0, 10, s1);
//	nd::matrix<int> m1 = nd::random::uniform(0, 10, s2);
//
//	nd::matrix<int> out = (m0 + m1);
//
//	nd::out::_h::print_vec1d(m0._m_begin(), 0, m0.size());
//
//	std::cout << "\n===========================\n";
//
//	nd::out::_h::print_vec1d(m1._m_begin(), 0, m1.size());
//
//	std::cout << "\n===========================\n";
//
//	std::cout << "shape :" << out.shape() << ", iter_type: "
//			<< static_cast<min_size_t>(out._m_iter_type()) << ln;
//
//	std::cout << "\n----------------------------\n";
//
//	nd::out::_h::print_vec1d(out._m_begin(), 0, out.size());
//}
//
