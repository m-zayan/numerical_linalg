/*
 * algorithm.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_WRAPPERS_ALGORITHM_HPP
#define SRC_WRAPPERS_ALGORITHM_HPP

#include "../common/algorithm.cpp"

#include "../typing/types.hpp"
#include "../handlers/exception.hpp"

namespace algorithm {

template<typename RT, typename T>
RT reduce_pairwise_selection(big_size_t begin, big_size_t end, vec1d<T> vec,
		std::function<RT(T&, T&)> func) {

	/*
	 * Error reduction is proportional to MAX_EXTRA_SPACE,
	 * such that, best case error (nearly, pairwise sum result)
	 * at MAX_EXTRA_SPACE = n/2 + 1, in other words,
	 * if(memory.size() > MAX_EXTRA_SPACE), is always false
	 */
	min_size_t MAX_EXTRA_SPACE = 64;

	big_size_t size = end - begin;
	big_size_t n_step = size - (size % 2);

	big_size_t start = begin;

	temporary_queue<RT> memory;

	T x1, x2;

	while (start < n_step) {

		// select pairs
		x1 = vec[start];
		x2 = vec[start + 1];

		start += 2;

		// sum
		memory.push(func(x1, x2));

		/* if queue size (memory) exceeds - MAX_EXTRA_SPACE,
		 * reduce memory size, (i.e. repeat pair-wise selelction)
		 */
		if (memory.size() > MAX_EXTRA_SPACE) {

			while (memory.size() > 1) {

				x1 = memory.next();
				x2 = memory.next();

				memory.push(func(x1, x2));
			}
		}
	}

	// odd size
	if (size % 2) {
		memory.push(vec[start]);
	}

	// repeat-pair-wise selelction | neglected
	while (memory.size() > 1) {

		x1 = memory.next();
		x2 = memory.next();

		memory.push(func(x1, x2));
	}

	return memory.front();
}

}

#endif /* SRC_WRAPPERS_ALGORITHM_HPP */
