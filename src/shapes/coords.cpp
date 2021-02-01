/*
 * coords.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./coords.hpp"

coords::coords() :
		shape( { }), ndim(0), size1d(0), nd_strides( { }), order('C'), own_data(
				1) {

}

coords::coords(shape_t shape) :
		shape(shape), ndim(shape.size()), size1d(
				shape.multiply(0, shape.size())), nd_strides(
				this->get_nd_strides(shape)), order('C'), own_data(1) {

}

coords::coords(shape_t shape, char order) :
		shape(shape), ndim(shape.size()), size1d(
				shape.multiply(0, shape.size())), nd_strides(
				this->get_nd_strides(shape)), order(order), own_data(1) {
}

coords::coords(shape_t shape, bool own_data) :
		shape(shape), ndim(shape.size()), size1d(
				shape.multiply(0, shape.size())), nd_strides(
				this->get_nd_strides(shape)), order('C'), own_data(own_data) {
}

coords::~coords() {
}

coords::coords(const coords &attr) :
		shape(attr.shape), ndim(attr.ndim), size1d(attr.size1d), nd_strides(
				attr.nd_strides), order(attr.order), own_data(attr.own_data) {

}

coords::coords(const coords &&attr) :
		shape(std::move(attr.shape)), ndim(attr.ndim), size1d(attr.size1d), nd_strides(
				std::move(attr.nd_strides)), order(attr.order), own_data(
				attr.own_data) {
}

coords coords::operator =(const coords &&attr) {

	this->shape = std::move(attr.shape);
	this->nd_strides = std::move(attr.nd_strides);
	this->ndim = attr.ndim;
	this->size1d = attr.size1d;
	this->order = attr.order;
	this->own_data = attr.own_data;

	return (*this);
}

shape_t coords::get_nd_strides(shape_t shape) {

	shape_t strides;

	if (shape.size() > 1) {

		strides.reserve(shape.size());

		// multiply - big size_t, have to be modified
		for (max_size_t i = 1; i < shape.size() - 1; i++) {

			max_size_t begin = i;
			max_size_t end = ndim - 1;

			strides.push_back(
					shape.multiply(begin, end) * shape[shape.size() - 1]);
		}

		strides.push_back(shape[shape.size() - 1]);
		strides.push_back(1);

	} else {

		strides.push_back(1);
	}

	return strides;
}

bool operator ==(const coords &attr1, const coords &attr2) {

	coords temp1 = std::move(attr1);
	coords temp2 = std::move(attr2);

	if (temp1.ndim == temp2.ndim) {
		for (max_size_t i = 0; i < temp1.ndim; i++) {
			if (temp1.shape[i] != temp2.shape[i]) {
				return false;
			}
		}
		return true;
	}

	else {
		return false;
	}
}
