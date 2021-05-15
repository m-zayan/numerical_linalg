/*
 * Iterator.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_ITERATOR_HPP
#define SRC_ITERATORS_ITERATOR_HPP

#include "../shapes/coords.hpp"

namespace nd::iterator {

class Iterator {

protected:

	big_size_t index_1d;
	big_size_t size;

	bool locked;

	void lock();

public:

	Iterator();
	Iterator(coords attr);

	virtual bool next();

	virtual big_size_t index() const;

	bool isLocked();

	void reset();

	virtual ~Iterator();
};

}

#endif /* SRC_ITERATORS_ITERATOR_HPP */