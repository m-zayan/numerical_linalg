/*
 * Pairwise.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_PAIRWISE_HPP
#define SRC_ITERATORS_PAIRWISE_HPP

#include "./RandomAccess.hpp"

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

namespace nd::iterator {

coords align_dim(coords &attr0, coords &attr1);

shape_t op_shape(const shape_t &shape0, const shape_t &shape1);

class Pairwise {

private:

	// aligned_attr
	vec1d<coords> attr_list;
	vec1d<RandomAccess*> iter_list;

	shape_t clipped_cache;

	shape_t& clipped_indices();
	RandomAccess& iter_of(min_size_t pair_index);

public:

	Pairwise() = delete;
	Pairwise(coords attr0, coords attr1);

	coords& aligned_coords(min_size_t pair_index);

	// pair_index --> {0: Pairwise::attr1, 1: Pairwise::attr2, 2: Pairwise::aligned_attr}

	shape_t& indices_at(big_size_t index_1d, min_size_t pair_index);
	big_size_t index_at(big_size_t index_1d, min_size_t pair_index);

	virtual ~Pairwise();
};

}

#endif /* SRC_ITERATORS_PAIRWISE_HPP */
