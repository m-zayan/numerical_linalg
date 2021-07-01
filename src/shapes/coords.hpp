/*
 * coords.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_SHAPES_COORDS_HPP
#define SRC_SHAPES_COORDS_HPP

#include <ostream>
#include <sstream>

// allocator.hpp --> #include "../typing/types.hpp"
#include "../typing/allocator.hpp"
#include "../wrappers/algorithm.hpp"

#include "../handlers/exception.hpp"

// =============================== nd::mem ===============================
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

// =============================== nd::state ===============================

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

	friend uflag8_t operator &(const shape_t &shape0, const shape_t &shape1);

	friend uflag8_t operator |(const shape_t &lhs, const shape_t &rhs);
	friend uflag8_t operator %(const shape_t &lhs, const shape_t &rhs);

};

/* =============================== IteratorType =============================== */

enum IteratorType {
	None, Linear, Random, Pair
};

/* =============================== coords ===============================
 *
 * 		matrix attributes (ex. dimensions)
 */

class coords {

private:

	static big_size_t get_size1d(shape_t &shape);
	static shape_t get_strides(shape_t &shape);

	static void check_strides(shape_t &shape, shape_t &strides);

public:

	shape_t shape;
	max_size_t ndim;

	big_size_t size1d; // shape.multiply(0, n)

	shape_t strides;
	shape_t axes;

	char order; // C-style, F-style, default : 'C'
	bool own_data; // inspired by, Numpy ndarray's flags;

	IteratorType iter_type;

	coords();

	coords(shape_t shape);

	coords(shape_t shape, char order);

	coords(shape_t shape, bool own_data, IteratorType iter_type);

	coords(shape_t shape, shape_t strides, bool own_data,
			IteratorType iter_type);

	coords(shape_t shape, shape_t axes, shape_t strides, bool own_data,
			IteratorType iter_type);

	coords& operator =(const coords &attr);

	coords permuted(const shape_t &axes, bool own_data) const;
	coords reverse_permute(bool own_data) const;
	coords swapaxes(max_size_t ax0, max_size_t ax1, bool own_data) const;
	coords transpose(bool own_data) const;

	coords reduce(max_size_t axis, bool keepdims) const;
	coords reduce_ndim(max_size_t start, max_size_t end, bool own_data) const;

	coords pad_dim(max_size_t new_ndim) const;
	coords pad_dim(max_size_t begin, max_size_t pad_size) const;

	void swapaxes(max_size_t ax0, max_size_t ax1);

	friend bool operator ==(const coords &attr1, const coords &attr2);

	virtual ~coords();

	coords(const coords &attr);
	coords(const coords &&attr);

};

// ======================================================================

namespace nd {

coords align_dim(coords &attr0, coords &attr1, std::string &&signature = "");

coords align_dim(coords &attr0, coords &attr1, vec1d<shape_t> axes,
		std::string &&signature = "");

coords align_dim_2d(coords &attr0, coords &attr1, std::string &&signature = "");

}

// ============================================= nd::parser::_h =============================================

namespace nd::parser::_h {

template<typename T>
void parse_shape(T &scalar, shape_t &out_shape,
		std::unordered_map<max_size_t, max_size_t> &depth_mp, max_size_t depth,
		std::string signature);

template<typename T>
void parse_shape(vec1d<T> &nested_vec1d, shape_t &out_shape,
		std::unordered_map<max_size_t, max_size_t> &depth_mp, max_size_t depth,
		std::string signature);

}

// =============================================   nd::parser   =============================================

namespace nd::parser {

template<typename T>
shape_t parse_shape(vec1d<T> nested_vec1d, std::string signature = "");

}

// =================================================================================================================

template<typename T>
void nd::parser::_h::parse_shape(T &scalar, shape_t &out_shape,
		std::unordered_map<max_size_t, max_size_t> &depth_mp, max_size_t depth,
		std::string signature) {

	return;
}

template<typename T>
void nd::parser::_h::parse_shape(vec1d<T> &nested_vec1d, shape_t &out_shape,
		std::unordered_map<max_size_t, max_size_t> &depth_mp, max_size_t depth,
		std::string signature) {

	max_size_t size = nested_vec1d.size();

	if (depth_mp.find(depth) != depth_mp.end()) {

		if (size != depth_mp[depth]) {

			throw nd::exception(signature + "Inconsistent Dimensions, "
					"dim = " + to_string(depth));
		}
	}

	else {

		depth_mp[depth] = size;

		out_shape.emplace_back(size);

	}

	for (max_size_t i = 0; i < size; i++) {

		nd::parser::_h::parse_shape(nested_vec1d[i], out_shape, depth_mp,
				depth + 1, signature);
	}

}

template<typename T>
shape_t nd::parser::parse_shape(vec1d<T> nested_vec1d, std::string signature) {

	std::unordered_map<max_size_t, max_size_t> depth_mp;

	shape_t out_shape;

	nd::parser::_h::parse_shape(nested_vec1d, out_shape, depth_mp, 0,
			signature);

	return out_shape;
}

// =================================================================================================================

inline bool require_no_iterator(const coords &attr) {

	return (attr.iter_type == IteratorType::None);
}

inline bool require_linear_iterator(const coords &attr) {

	return (attr.iter_type == IteratorType::Linear);
}

inline bool require_pair_iterator(const coords &attr) {

	return (attr.iter_type == IteratorType::Pair);
}

#endif /* SRC_SHAPES_COORDS_HPP */
