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

	shape_t strides() const;
	shape_t shape() const;
	shape_t axes() const;

	max_size_t ndim() const;
	big_size_t size() const;

	char order() const;
	bool own_data() const;

	uflag8_t iter_type() const;

public:

	RandomAccess() = delete;

	RandomAccess(coords attr);

	shape_t indices_at(big_size_t index_1d) const;

	big_size_t index_at(shape_t indices) const;
	big_size_t index_at(big_size_t index_1d) const;

	big_size_t reversed_index_at(big_size_t index_1d) const;

	bool is_cycle_root(big_size_t index_1d) const;

	virtual ~RandomAccess();
};
}

#endif /* SRC_ITERATORS_RandomAccess_HPP */
