/*
 * factory.hpp
 *
 *      Author: Z. Mohamed
 *
 *      [Iterator Factory]
 */

#ifndef SRC_ITERATORS_FACTORY_HPP
#define SRC_ITERATORS_FACTORY_HPP

#include "./Iterator.hpp"

namespace nd::iterator {

inline Iterator* init_iterator(const coords &attr) {

	if (!undefined_iterator(attr)) {

		return (new Iterator(attr));

	} else {

		throw nd::exception(
				"nd::iterator::init_iterator(...), Invalid Iterator Type");
	}
}

inline void free_iterator(Iterator *it) {

	delete it;
}

}

#endif /* SRC_ITERATORS_FACTORY_HPP */
