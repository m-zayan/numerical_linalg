/*
 * RandomAccess.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_DEPRECATED_ITERATORS_RANDOMACESS_HPP
#define SRC_DEPRECATED_ITERATORS_RANDOMACESS_HPP

#include "./Iterator.hpp"

namespace nd::deprecated::iterator {
class RandomAccess {

private:

	coords attr;

	shape_t indices_cache;

	strides_t& strides();
	shape_t& shape();
	shape_t& axes();

	max_size_t ndim() const;
	big_size_t size() const;

	char order() const;
	bool own_data() const;

	IteratorType iter_type() const;

	shape_t& indices();

public:

	RandomAccess() = delete;
	RandomAccess(coords attr);

	shape_t& indices_at(big_size_t index_1d);

	big_size_t nd_index_at(shape_t &indices);
	big_size_t nd_index_at(shape_t &&indices);

	big_size_t index_at(big_size_t index_1d);

	big_size_t reversed_index_at(big_size_t index_1d, coords &prev_attr,
			RandomAccess &prev_rndIter, strides_t &reordered_strides);

	bool is_cycle_root(big_size_t index_1d, coords &prev_attr,
			nd::deprecated::iterator::RandomAccess &prev_rndIter,
			strides_t &reordered_strides);

	virtual ~RandomAccess();
};
}

#endif /* SRC_DEPRECATED_ITERATORS_RANDOMACESS_HPP */
