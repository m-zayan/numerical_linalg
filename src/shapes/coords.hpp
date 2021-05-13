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

namespace nd::mem {
/*
 * Most of nd::matrix ops's implementation, follows D&C (iteratively),
 *
 * mainly to make
 * 	np::apply_along_axis(...) reusable, for all numeric ops, (ex. sum, var)
 *
 * reciprocally, it improves the numerical stability for some numeric ops
 *
 * number_of_splits = shape[axis] / nd::mem::AUX_SIZE
 */
extern bounded_t<max_size_t> AUX_SIZE;

inline max_size_t clip_dim(max_size_t dim_size) {

	return std::min(dim_size, static_cast<max_size_t>(AUX_SIZE));
}

}

namespace nd::state {
/*
 * BroadcastingLevel = 0, broadcasting in not allowed,
 * i.e. for all nd::matrix ops shapes should exactly match.
 *
 * BroadcastingLevel = 1, padding for nd::matrix::shape() should be explicitly defined
 *
 * BroadcastingLevel = 2, implicit padding for nd::matrix::shape(),
 * 	ex. (3, 3) might be considered as (1, 3, 3) implicitly
 *
 *
 */

extern bounded_t<uflag8_t> BroadcastingLevel;

}

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

namespace nd {

coords align_dim(coords &attr0, coords &attr1);

}

#endif /* SRC_SHAPES_COORDS_HPP */
