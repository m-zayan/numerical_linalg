/*
 * algorithms.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_ALGORITHM_HPP
#define SRC_ALGORITHM_HPP

#include <queue>

#include "../typing/types.hpp"
#include "../typing/allocator.cpp"

template<typename T>
class algorithm {

protected:
	static T __pairwise_summation(big_size_t begin, big_size_t end, T *x);
	static T __naive_summation(big_size_t begin, big_size_t end, T *x);

public:

	algorithm();

	// summation algorithms
	static T naive_summation(big_size_t begin, big_size_t end,
			std::vector<T> vec);
	static T kahan_summation(big_size_t begin, big_size_t end,
			std::vector<T> vec);
	static T pairwise_summation(big_size_t begin, big_size_t end,
			std::vector<T> vec);
	static T shift_reduce_sum(big_size_t begin, big_size_t end,
			std::vector<T> vec);

	// poor performance (i.e. not efficient)
	static T pairwise_selection_sum(big_size_t begin, big_size_t end,
			std::vector<T> vec);

	virtual ~algorithm();
};

#endif /* SRC_ALGORITHM_HPP */
