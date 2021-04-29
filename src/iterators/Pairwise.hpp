/*
 * Pairwise.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_PAIRWISE_HPP
#define SRC_ITERATORS_PAIRWISE_HPP

#include "./RandomAccess.hpp"

namespace nd::iterator {

coords align_dim(coords &attr0, coords &attr1);

class Pairwise {

private:

	// aligned_attr
	coords attr2;

	coords attr0;
	coords attr1;

	RandomAccess rndIter0;
	RandomAccess rndIter1;

	RandomAccess rndIter2;

public:

	Pairwise() = delete;
	Pairwise(coords attr0, coords attr1);

	coords aligned_coords(uflag8_t pair_index) const;

	// pair_index --> {0: Pairwise::attr1, 1: Pairwise::attr2, 2: Pairwise::aligned_attr}

	shape_t indices_at(big_size_t index_1d, uflag8_t pair_index) const;
	big_size_t index_at(big_size_t index_1d, uflag8_t pair_index) const;

	virtual ~Pairwise();
};

}

#endif /* SRC_ITERATORS_PAIRWISE_HPP */
