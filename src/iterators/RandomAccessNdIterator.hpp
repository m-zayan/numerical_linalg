/*
 * RandomAccessNdIterator.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_RANDOMACCESSNDITERATOR_HPP
#define SRC_ITERATORS_RANDOMACCESSNDITERATOR_HPP

#include "../shapes/coords.hpp"

class RandomAccessNdIterator {

private:

	coords attr;

	shape_t strides() const;
	shape_t shape() const;
	max_size_t ndim() const;
	big_size_t size() const;

	char order() const;
	bool own_data() const;

public:

	RandomAccessNdIterator() = delete;
	RandomAccessNdIterator(coords attr);

	RandomAccessNdIterator& operator =(const coords &attr);

	big_size_t index_at(shape_t indices) const;
	big_size_t index_at(big_size_t index_1d) const;

	virtual ~RandomAccessNdIterator();
};

#endif /* SRC_ITERATORS_RANDOMACCESSNDITERATOR_HPP */
