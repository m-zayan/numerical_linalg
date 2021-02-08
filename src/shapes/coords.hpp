/*
 * coords.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_SHAPES_COORDS_HPP
#define SRC_SHAPES_COORDS_HPP

#include <ostream>
#include <sstream>

#include "../iterators/SequentialNdIterator.hpp"

// matrix attributes (ex. dimensions)
class coords {

private:
	shape_t get_nd_strides(shape_t shape);

public:

	shape_t shape;
	max_size_t ndim;

	big_size_t size1d; // shape.multiply(0, n)

	shape_t nd_strides;

	char order; // C-style, F-style, default : 'C'
	bool own_data; // inspired by, Numpy ndarray's flags

	coords();
	coords(shape_t shape);
	coords(shape_t shape, char order);
	coords(shape_t shape, bool own_data);

	coords operator =(const coords &&attr);

	friend bool operator ==(const coords &attr1, const coords &attr2);

	virtual ~coords();

	coords(const coords &attr);
	coords(const coords &&attr);

};

#endif /* SRC_SHAPES_COORDS_HPP */
