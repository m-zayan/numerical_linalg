/*
 * Pairwise.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_PAIRWISE_HPP
#define SRC_ITERATORS_PAIRWISE_HPP

#include "./RandomAccess.hpp"

namespace nd::iterator {

coords align_dim(coords attr1, coords attr2);

class Pairwise {

private:

	coords attr1;
	coords attr2;

	coords aligned_attr;

	RandomAccess rndIter;

public:

	Pairwise() = delete;
	Pairwise(coords attr1, coords attr2);

	coords aligned_coords() const;

	// pair_index --> {0: Pairwise::attr1, 1: Pairwise::attr2, 2: Pairwise::aligned_attr}

	shape_t indices_at(big_size_t index_1d, uflag8_t pair_index) const;
	big_size_t index_at(big_size_t index_1d, uflag8_t pair_index) const;

	virtual ~Pairwise();
};

}

#endif /* SRC_ITERATORS_PAIRWISE_HPP */
