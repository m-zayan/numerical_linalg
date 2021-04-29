/*
 * nd_broadcasting.cpp
 *
 *	Author: Z. Mohamed
 */

#include "test_api.hpp"

void test_api::nd_broadcasting() {

	shape_t s1 = { 3, 1, 3, 2 };
	shape_t s2 = { 2, 3, 1 };

	std::cout << static_cast<min_size_t>((s1 & s2)) << "\n";
}
