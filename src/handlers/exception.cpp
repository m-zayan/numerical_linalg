/*
 * exception.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./exception.hpp"

nd::exception::exception(const std::string &message) {
	this->message = message;
}

const char* nd::exception::exception::what() const throw () {
	return this->message.c_str();
}

nd::exception::~exception() {
}

