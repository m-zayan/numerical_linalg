/*
 * nd_seq_iter.cpp
 *
 *	Author: Z. Mohamed
 */

#include <iostream>
#include <memory>

#include "../src/iterators/SequentialNdIterator.hpp"

#define ln '\n'

int main() {

	shape_t shape = { 4, 3, 2, 2 };
	max_size_t ndim = shape.size();

	SequentialNdIterator seqIter(shape);

	max_size_t count = 0;

	seqIter.icurrent().print_vec1d(0, ndim);
	std::cout << " : " << count++ << ln;

	while (!seqIter.isLoked()) {

		seqIter.next().print_vec1d(0, ndim);
		std::cout << " : " << count++ << ln;
	}
}
