/*
 * nd_align_dim.cpp
 *
 *      Author: Z. Mohamed
 */

#include "../../src/shapes/coords.hpp"
#define ln '\n'

int main() {

	shape_t s0 = { 3, 4, 5, 3 };
	shape_t s1 = { 6, 4, 2, 3 };

	vec1d<shape_t> axes = { { 0, 1 }, { 3, 1 } };

	coords attr0(s0), attr1(s1);

	coords out_attr0 = nd::align_dim(attr0, attr1, axes);

	std::cout << attr0.shape << ln;
	std::cout << attr1.shape << ln;
	std::cout << out_attr0.shape << ln;

	std::cout << "---------------\n";
	std::cout << attr0.reduce_ndim(0, 4).shape << ln;

	std::cout << "====================\n";

	shape_t s2 = { 6, 5, 4, 3 };
	shape_t s3 = { 1, 5, 3, 4 };

	coords attr2(s2), attr3(s3);

	coords out_attr1 = nd::align_dim_2d(attr2, attr3);

	std::cout << attr2.shape << ", " << attr2.axes << ln;
	std::cout << attr3.shape << ", " << attr3.axes << ln;
	std::cout << out_attr1.shape << ln;

}

