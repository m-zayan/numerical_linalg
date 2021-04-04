/*
 * weak_ptr.h
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPING_STL_WRAPPER_WEAK_PTR_HPP
#define SRC_TYPING_STL_WRAPPER_WEAK_PTR_HPP

#include <memory>

template<typename T>
class weak_ptr: public std::weak_ptr<T> {
public:

	using std::weak_ptr<T>::weak_ptr;

	std::shared_ptr<T> get() const {
		return this->lock();
	}
};

#endif /* SRC_TYPING_STL_WRAPPER_WEAK_PTR_HPP */
