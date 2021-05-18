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

		// apply function
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

template<typename RT, typename T>
RT reduce_pairwise(big_size_t begin, big_size_t end, T *x,
		std::function<RT(T&, T&)> func) {

	big_size_t n = end - begin;

	if (n <= 1) {
		return x[0];
	}

	RT x0 = reduce_pairwise<RT, T>(begin, n / 2, x, func);
	RT x1 = reduce_pairwise<RT, T>(begin, n - n / 2, x + n / 2, func);

	return func(x0, x1);

}

template<typename RT, typename T = RT>
RT sum(big_size_t begin, big_size_t end, T *x) {

	return algorithm::_h::pairwise_summation<RT, T>(begin, end, x);
}

// a ∩ b'
template<typename T>
vec1d<T> a_intersect_b_comp(vec1d<T> a, vec1d<T> b) {

	vec1d<T> result;

	std::unordered_set<T> b_set;

	for (auto &elem : b) {
		b_set.insert(elem);
	}

	for (auto &elem : a) {

		if (b_set.find(elem) == b_set.end()) {
			result.emplace_back(elem);
		}
	}

	return result;
}

}

#endif /* SRC_WRAPPERS_ALGORITHM_HPP */
