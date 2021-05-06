/*
 * coords.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_SHAPES_COORDS_HPP
#define SRC_SHAPES_COORDS_HPP

#include <ostream>
#include <sstream>

#include "../typing/types.hpp"
#include "../handlers/exception.hpp"

// =============================== shape_t ===============================
class shape_t: public vec1d<max_size_t> {

public:

	using vec1d<max_size_t>::vec1d;

	friend std::ostream& operator <<(std::ostream &os, shape_t shape);
	friend uflag8_t operator &(const shape_t &shape1, const shape_t &shape2);
};

/* =============================== coords ===============================
 *
 * 		matrix attributes (ex. dimensions)
 */

class coords {

private:

	shape_t get_strides(shape_t shape);
	void check_strides(shape_t shape, shape_t strides);

public:

	shape_t shape;
	max_size_t ndim;

	big_size_t size1d; // shape.multiply(0, n)

	shape_t strides;
	shape_t axes;

	char order; // C-style, F-style, default : 'C'
	bool own_data; // inspired by, Numpy ndarray's flags;

	uflag8_t iter_type;

	coords();

	coords(shape_t shape);

	coords(shape_t shape, char order);

	coords(shape_t shape, bool own_data, uflag8_t iter_type);

	coords(shape_t shape, shape_t strides, bool own_data, uflag8_t iter_type);

	coords(shape_t shape, shape_t axes, shape_t strides, bool own_data,
			uflag8_t iter_type);

	coords& operator =(const coords &attr);

	coords permuted(const shape_t &axes, bool own_data) const;
	coords reverse_permute(bool own_data) const;
	coords swapaxes(max_size_t ax0, max_size_t ax1, bool own_data) const;
	coords reduce(max_size_t axis, bool keepdims) const;
	coords pad_dim(max_size_t new_ndim) const;

	void swapaxes(max_size_t ax0, max_size_t ax1);

	friend bool operator ==(const coords &attr1, const coords &attr2);

	virtual ~coords();

	coords(const coords &attr);
	coords(const coords &&attr);

};

#endif /* SRC_SHAPES_COORDS_HPP */
