/*
 * RandomAccess.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_RandomAccess_HPP
#define SRC_ITERATORS_RandomAccess_HPP

#include "../shapes/coords.hpp"

namespace nd::iterator {
class RandomAccess {

private:

	coords attr;

	shape_t indices_cache;

	shape_t& strides();
	shape_t& shape();
	shape_t& axes();

	max_size_t ndim() const;
	big_size_t size() const;

	char order() const;
	bool own_data() const;

	uflag8_t iter_type() const;

	shape_t& indices();

public:

	RandomAccess() = delete;
	RandomAccess(coords attr);

	shape_t& indices_at(big_size_t index_1d);

	big_size_t nd_index_at(shape_t &indices);
	big_size_t index_at(big_size_t index_1d);

	big_size_t reversed_index_at(big_size_t index_1d);

	bool is_cycle_root(big_size_t index_1d);

	virtual ~RandomAccess();
};
}

#endif /* SRC_ITERATORS_RandomAccess_HPP */
