/*
 * temporary_queue.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_TYPING_GTYPES_STL_WRAPPER_TEMPORARY_QUEUE_HPP
#define SRC_TYPING_GTYPES_STL_WRAPPER_TEMPORARY_QUEUE_HPP

#include <queue>

template<typename T>
class temporary_queue: public std::queue<T> {

public:

	using std::queue<T>::queue;

	T next() {

		if (this->empty()) {

			// <stdexcept>
			throw std::logic_error(
					"Calling temporary_queue<T>::next(), for an Empty temporary_queue<T>\n\t"
							"temporary_queue<T>::empty() == true");
		}

		T value = this->front();

		this->pop();

		return value;
	}

	virtual ~temporary_queue() {

	}
};
#endif /* SRC_TYPING_GTYPES_STL_WRAPPER_TEMPORARY_QUEUE_HPP */
