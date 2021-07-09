/*
 * factory.hpp
 *
 *      Author: Z. Mohamed
 *
 *      [Iterator Factory]
 */

#ifndef SRC_ITERATORS_FACTORY_HPP
#define SRC_ITERATORS_FACTORY_HPP

#include "./Sequential.hpp"

#include "./CIterator.hpp"

namespace nd::iterator {

inline Iterator* init_iterator(const coords &attr) {

	Iterator *iter;

	if (require_no_iterator(attr) || is_scalar(attr)) {

		Iterator *trivialIter = new Iterator(attr);

		iter = trivialIter;

	}

	else if (require_linear_iterator(attr)) {

		Sequential *seqIter = new Sequential(attr);

		iter = seqIter;
	}

	else {

		throw nd::exception(
				"nd::iterator::init_iterator(...), Invalid Iterator Type");
	}

	return iter;
}

inline void free_iterator(Iterator *iter) {

	delete iter;
}

}

#endif /* SRC_ITERATORS_FACTORY_HPP */
