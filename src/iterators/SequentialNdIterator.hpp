/*
 * SequentialNdIterator.hpp
 *
 *	Author: Z. Mohamed
 *
 *	vec1d strides iterator, [sequential permutation]
 */

#ifndef SRC_ITERATORS_SEQUENTIALNDITERATOR_HPP_
#define SRC_ITERATORS_SEQUENTIALNDITERATOR_HPP_

#include "../common/vec1d.cpp"

class SequentialNdIterator {

private:

	shape_t shape;
	max_size_t dim_bounds;

	// indices
	shape_t current;

	max_size_t cur_dim;

	flag8_t proceed(big_t i);
	flag8_t update_state(flag8_t state);
	void next_prem();

	bool locked;

	void lock();

public:

	SequentialNdIterator() = delete;

	SequentialNdIterator(shape_t shapes);

	shape_t next();
	shape_t icurrent();

	bool isLoked();

	void unlock();
	void reset();

	virtual ~SequentialNdIterator();
};

#endif /* SRC_ITERATORS_SequentialNdIterator_HPP_ */
