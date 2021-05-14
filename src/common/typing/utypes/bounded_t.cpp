/*
 * bounded_t.cpp
 *
 *	Author: Z. Mohamed
 */

#include "bounded_t.hpp"

template<typename T>
bounded_t<T>::bounded_t(std::vector<T> bounds) :
		bounds(bounds), signature(""), value(bounds[0]) {

}

template<typename T>
bounded_t<T>::bounded_t(std::vector<T> bounds, std::string signature, T value) :
		bounds(bounds), signature(signature) {

	this->validate_bounds(value);

	this->value = value;

}

template<typename T>
void bounded_t<T>::validate_bounds(T val) {

	for (size_t i = 0; i < this->bounds.size(); i++) {
		if (val == this->bounds[i]) {
			return;
		}
	}

	throw std::logic_error(
			"Invalid assignment op: " + this->signature
					+ ", Value Out of Range, [lower_bound, upper_bound]");

}

template<typename T>
bounded_t<T>& bounded_t<T>::operator=(T value) {

	this->validate_bounds(value);

	this->value = value;

	return (*this);
}

template<typename T>
bounded_t<T>::operator T() const {
	return this->value;
}

template<typename T>
bounded_t<T>::~bounded_t() {
}

template<typename T>
std::ostream& operator <<(std::ostream &os, const bounded_t<T> &bndt) {

	os << bndt.value;
	return os;
}

