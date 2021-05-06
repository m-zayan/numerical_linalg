/*
 * Sequential.hpp
 *
 *	Author: Z. Mohamed
 *
 *	N-dimensional iterator to index vec1d
 */

#ifndef SRC_ITERATORS_SEQUENTIAL_HPP
#define SRC_ITERATORS_SEQUENTIAL_HPP

#include "../shapes/coords.hpp"

namespace nd::iterator {

class Sequential {

private:

	shape_t shape;
	max_size_t dim_bounds;

	max_size_t axis;
	max_size_t mov_axis;

	// indices
	shape_t current;

	bool locked;

	flag8_t proceed(big_t i);
	flag8_t update_state(flag8_t state);
	void next_prem();

	void lock();

public:

	Sequential() = delete;

	Sequential(shape_t shape);

	void next();
	shape_t icurrent() const;

	max_size_t iaxis();
	bool isLoked();

	void unlock();
	void reset();

	virtual ~Sequential();
};
}

#endif /* SRC_ITERATORS_SEQUENTIAL_HPP */
