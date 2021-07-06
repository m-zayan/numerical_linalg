/*
 * cond_iterator.cpp
 *
 *      Author: Z. Mohamed
 */

#include "../../src/iterators/CIterator.hpp"

#define ln '\n'

int main() {

	coords attr0( { 1, 3, 2 }, true, IteratorType::None);
	coords attr1( { 3, 2, 4 }, true, IteratorType::None);
	coords attr2( { 6, 3, 4, 2 }, true, IteratorType::None);
	coords attr3( { 1000000, 6, 3, 2, 3 }, true, IteratorType::None);
	coords attr4( { 3, 3 }, true, IteratorType::None);

	CIterator iter( { &attr0, &attr1, &attr2, &attr3, &attr4 });

	iter.op_2d_alignment("init-test, ");

	std::cout << iter.root_coords().shape << ln;

	std::cout << iter.ith_ndim(0) << ln;
}

