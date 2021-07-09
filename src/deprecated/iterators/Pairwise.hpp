/*
 * Pairwise.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_DEPRECATED_ITERATORS_PAIRWISE_HPP
#define SRC_DEPRECATED_ITERATORS_PAIRWISE_HPP

#include "./RandomAccess.hpp"

namespace nd::iterator {

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

	coords aligned_coords(min_size_t pair_index);

	// pair_index --> {0: Pairwise::attr1, 1: Pairwise::attr2, 2: Pairwise::aligned_attr}
	shape_t& indices_at(big_size_t index_1d, min_size_t pair_index);
	big_size_t index_at(big_size_t index_1d, min_size_t pair_index);

	virtual ~Pairwise();
};

}

#endif /* SRC_DEPRECATED_ITERATORS_PAIRWISE_HPP */
