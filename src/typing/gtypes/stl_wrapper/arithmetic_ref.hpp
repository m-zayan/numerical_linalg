/*
 * arithmetic_ref.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPING_STL_WRAPPER_ARITHMETIC_REF_HPP
#define SRC_TYPING_STL_WRAPPER_ARITHMETIC_REF_HPP

#include "../types.hpp"

template<typename T, bool own_data = true>
class arithmetic_ref: public ref_t<own_data, T>::type {

public:

	using ptr_t = typename ref_t<own_data, T>::type;
	using ptr_t::operator=;

	arithmetic_ref(T *val) :
			ptr_t(val) {
	}

	ptr_t& operator=(const ptr_t &p) {

		return ptr_t(new T(*p.get()));
	}

	ptr_t& operator=(const T *val) {

		return ptr_t(val);
	}

	ptr_t operator +(const ptr_t &p) {

		T r = *this->get() + *p.get();

		return ptr_t(new T(r));
	}

	ptr_t& operator +=(const ptr_t &p) {

		*this->get() += *p.get();

		return (*this);
	}

	ptr_t operator +(const T &val) {

		T r = *this->get() + val;

		return ptr_t(new T(r));
	}

	ptr_t& operator +=(const T &val) {

		*this->get() += val;

		return (*this);
	}

	ptr_t operator -(const ptr_t &p) {

		T r = *this->get() - *p.get();

		return ptr_t(new T(r));
	}

	ptr_t& operator -=(const ptr_t &p) {

		*this->get() -= *p.get();

		return (*this);
	}

	ptr_t operator -(const T &val) {

		T r = *this->get() - val;

		return ptr_t(new T(r));
	}

	ptr_t& operator -=(const T &val) {

		*this->get() -= val;

		return (*this);
	}

	ptr_t operator *(const ptr_t &p) {

		T r = (*this->get()) * (*p.get());

		return ptr_t(new T(r));
	}

	ptr_t& operator *=(const ptr_t &p) {

		*this->get() *= (*p.get());

		return (*this);
	}

	ptr_t operator *(const T &val) {

		T r = *this->get() * val;

		return ptr_t(new T(r));
	}

	ptr_t& operator *=(const T &val) {

		*this->get() *= val;

		return (*this);
	}

	ptr_t operator /(const ptr_t &p) {

		T r = (*this->get()) / (*p.get());

		return ptr_t(new T(r));
	}

	ptr_t& operator /=(const ptr_t &p) {

		*this->get() /= (*p.get());

		return (*this);
	}

	ptr_t operator /(const T &val) {

		T r = *this->get() * val;

		return ptr_t(new T(r));
	}

	ptr_t& operator /=(const T &val) {

		*this->get() /= val;

		return (*this);
	}

};
#endif /* SRC_TYPING_STL_WRAPPER_ARITHMETIC_REF_HPP */
