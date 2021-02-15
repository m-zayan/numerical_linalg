/*
 * RandomAccessNdIterator.h
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_RANDOMACCESSNDITERATOR_HPP
#define SRC_ITERATORS_RANDOMACCESSNDITERATOR_HPP

#include "./SequentialNdIterator.hpp"

class RandomAccessNdIterator {

private:

	coords attr;

	inline shape_t strides() const;
	inline shape_t shape() const;
	inline max_size_t ndim() const;
	inline big_size_t size() const;
	inline char order() const;
	inline bool own_data() const;

public:

	RandomAccessNdIterator() = delete;
	RandomAccessNdIterator(coords attr);

	RandomAccessNdIterator& operator =(const coords &attr);

	big_size_t index_at(shape_t indices) const;
	big_size_t index_at(big_size_t index_1d) const;

	virtual ~RandomAccessNdIterator();
};

#endif /* SRC_ITERATORS_RANDOMACCESSNDITERATOR_HPP */
