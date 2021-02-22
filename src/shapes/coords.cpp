/*
 * coords.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./coords.hpp"

coords::coords() :
		shape( { }), ndim(0), size1d(0), strides( { }), order('C'), own_data(1) {

}

coords::coords(shape_t shape) :
		shape(shape), ndim(shape.size()), size1d(
				shape.multiply(0, shape.size())), strides(
				this->get_strides(shape)), order('C'), own_data(1) {

}

coords::coords(shape_t shape, char order) :
		shape(shape), ndim(shape.size()), size1d(
				shape.multiply(0, shape.size())), strides(
				this->get_strides(shape)), order(order), own_data(1) {
}

coords::coords(shape_t shape, bool own_data) :
		shape(shape), ndim(shape.size()), size1d(
				shape.multiply(0, shape.size())), strides(
				this->get_strides(shape)), order('C'), own_data(own_data) {
}

coords::coords(shape_t shape, shape_t strides, bool own_data) {

	this->check_strides(shape, strides);

	this->shape = shape;
	this->strides = strides;
	this->ndim = shape.size();
	this->size1d = shape.multiply(0, shape.size());
	this->order = 'C';
	this->own_data = own_data;
}

coords::~coords() {
}

coords::coords(const coords &attr) :
		shape(attr.shape), ndim(attr.ndim), size1d(attr.size1d), strides(
				attr.strides), order(attr.order), own_data(attr.own_data) {

}

coords::coords(const coords &&attr) :
		shape(std::move(attr.shape)), ndim(attr.ndim), size1d(attr.size1d), strides(
				std::move(attr.strides)), order(attr.order), own_data(
				attr.own_data) {
}

coords coords::operator =(const coords &&attr) {

	this->shape = std::move(attr.shape);
	this->strides = std::move(attr.strides);
	this->ndim = attr.ndim;
	this->size1d = attr.size1d;
	this->order = attr.order;
	this->own_data = attr.own_data;

	return (*this);
}

shape_t coords::get_strides(shape_t shape) {

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

void coords::check_strides(shape_t shape, shape_t strides) {

	for (max_size_t i = 0; i < shape.size() - 1; i++) {

		if (strides[i] % shape[i] != 0
				|| (strides[i] / shape[i]) != strides[i + 1]) {

			nd::exception("Invalid coords(shape, strides), shape, "
					"doesn't match with the given strides");
		}
	}
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
