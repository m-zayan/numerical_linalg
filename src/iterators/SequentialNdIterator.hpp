/*
 * SequentialNdIterator.hpp
 *
 *	Author: Z. Mohamed
 *
 *	vec1d strides iterator, [sequential permutation]
 */

#ifndef SRC_ITERATORS_SEQUENTIALNDITERATOR_HPP
#define SRC_ITERATORS_SEQUENTIALNDITERATOR_HPP

#include "../common/vec1d.cpp"

class SequentialNdIterator {

private:

	shape_t shape;
	max_size_t dim_bounds;

	// indices
	shape_t current;
	max_size_t axis;
	max_size_t mov_axis;

	flag8_t proceed(big_t i);
	flag8_t update_state(flag8_t state);
	void next_prem();

	bool locked;

	void lock();

public:

	SequentialNdIterator() = delete;

	SequentialNdIterator(shape_t shapes);

	shape_t next();
	shape_t icurrent() const;

	max_size_t iaxis();
	bool isLoked();

	void unlock();
	void reset();

	virtual ~SequentialNdIterator();
};

#endif /* SRC_ITERATORS_SequentialNdIterator_HPP */
