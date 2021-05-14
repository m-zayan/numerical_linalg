/*
 * Sequential.hpp
 *
 *	Author: Z. Mohamed
 *
 *	N-dimensional iterator to index vec1d
 */

#ifndef SRC_ITERATORS_SEQUENTIAL_HPP
#define SRC_ITERATORS_SEQUENTIAL_HPP

#include "./Iterator.hpp"

namespace nd::iterator {

class Sequential: public Iterator {

private:

	coords attr;

	max_size_t dim_bounds;

	max_size_t axis;
	max_size_t mov_axis;

	vec1d<big_size_t> bounds;

	// indices
	shape_t current;

	// index_1d
	big_size_t index_1d;

	bool locked;

	shape_t& shape();
	shape_t& strides();

	flag8_t proceed(big_t i);
	flag8_t update_state(flag8_t state);
	void next_prem();

	void lock();

public:

	Sequential() = delete;

	Sequential(coords attr);

	virtual bool next();

	virtual big_size_t index() const;

	shape_t indices() const;

	max_size_t iaxis();
	bool isLocked();

	void unlock();
	void reset();

	virtual ~Sequential();
};
}

#endif /* SRC_ITERATORS_SEQUENTIAL_HPP */
