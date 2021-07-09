/*
 * Iterator.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_DEPRECATED_ITERATORS_ITERATOR_HPP
#define SRC_DEPRECATED_ITERATORS_ITERATOR_HPP

#include "../../shapes/coords.hpp"

namespace nd::deprecated::iterator {

class Iterator {

protected:

	big_size_t index_1d;
	big_size_t size;

	IteratorType iter_type;

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

#endif /* SRC_DEPRECATED_ITERATORS_ITERATOR_HPP */
