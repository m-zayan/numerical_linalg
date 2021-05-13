/*
 * PairwiseSequential.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_PAIRWISESEQUENTIAL_HPP
#define SRC_ITERATORS_PAIRWISESEQUENTIAL_HPP

#include "./Sequential.hpp"

namespace nd::iterator {

class PairwiseSequential {

private:

	// aligned_attr
	vec1d<coords> attr_list;

	max_size_t dim_bounds;

	max_size_t axis;
	max_size_t mov_axis;

	vec1d<vec1d<big_size_t>> bounds;

	// indices
	vec1d<shape_t> current;

	// index_1d
	vec1d<big_size_t> index_1d;

	bool locked;

	max_size_t shape(max_size_t axis, min_size_t pair_index);
	max_size_t strides(max_size_t axis, min_size_t pair_index);

	big_size_t& ibounds(max_size_t axis, min_size_t pair_index);

	max_size_t& icurrent(max_size_t axis, min_size_t pair_index);
	big_size_t& iindex(min_size_t pair_index);

	flag8_t proceed(big_t i);
	flag8_t update_state(flag8_t state);

	void chunk_proceed(max_size_t axis, min_size_t pair_index);
	void clip(max_size_t axis, min_size_t pair_index);

	void next_prem();

	void lock();

public:

	PairwiseSequential() = delete;

	PairwiseSequential(coords attr0, coords attr1);

	coords aligned_coords(min_size_t pair_index);

	bool next();

	// pair_index --> {0, 1, 2}
	shape_t indices(min_size_t pair_index);
	big_size_t index(min_size_t pair_index);

	max_size_t iaxis();
	bool isLoked();

	void unlock();
	void reset();

	virtual ~PairwiseSequential();
};

}
#endif /* SRC_ITERATORS_PAIRWISESEQUENTIAL_HPP */
