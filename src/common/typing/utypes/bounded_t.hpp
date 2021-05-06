/*
 * bounded_t.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPING_UTYPES_BOUNDED_T_HPP
#define SRC_TYPING_UTYPES_BOUNDED_T_HPP

#include <iostream>
#include <vector>

template<typename T>
class bounded_t {
private:

	T value;

	void validate_bounds(T value);

public:

	const std::vector<T> bounds;
	const std::string signature;

	bounded_t() = delete;
	bounded_t(bounded_t&) = delete;

	bounded_t(std::vector<T> bounds);
	bounded_t(std::vector<T> bounds, std::string signature, T value);

	bounded_t& operator=(T value);

	operator T() const;

	template<typename U>
	friend std::ostream& operator <<(std::ostream &os,
			const bounded_t<U> &bndt);

	virtual ~bounded_t();
};

template<typename T, T ... Bounds>
class bounded_initializer: public bounded_t<T> {

public:

	bounded_initializer() :
			bounded_t<T>::bounded_t( { Bounds ... }) {
	}

	bounded_initializer(std::string signature, T value) :
			bounded_t<T>::bounded_t( { Bounds ... }, signature, value) {

	}

};

#endif /* SRC_TYPING_UTYPES_BOUNDED_T_HPP */
