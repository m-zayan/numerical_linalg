/*
 * mask.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_TYPING_UTYPES_HPP_MASK_HPP
#define SRC_TYPING_UTYPES_HPP_MASK_HPP

#include <iostream>

class mask_t {

private:

	bool val = false;

public:

	friend std::ostream& operator <<(std::ostream &os, mask_t mask) {

		os << mask.val;
		return os;
	}

	mask_t& operator=(mask_t mask) {
		this->val = mask.val;
		return (*this);
	}

	mask_t& operator=(bool val) {
		this->val = val;
		return (*this);
	}

};
#endif /* SRC_TYPING_UTYPES_HPP_MASK_HPP */
