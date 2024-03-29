/*
 * algorithms.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_ALGORITHM_HPP
#define SRC_ALGORITHM_HPP

#include <algorithm>
#include <cmath>

#include "./typing/gtypes/types.hpp"

namespace algorithm::_h {

template<typename RT, typename T>
RT pairwise_summation(big_size_t begin, big_size_t end, T *x);

template<typename RT, typename T>
RT naive_summation(big_size_t begin, big_size_t end, T *x);

}

namespace algorithm {

// summation algorithms
template<typename RT, typename T>
RT naive_summation(big_size_t begin, big_size_t end, std::vector<T> vec);

template<typename RT, typename T>
RT kahan_summation(big_size_t begin, big_size_t end, std::vector<T> vec);

template<typename RT, typename T>
RT pairwise_summation(big_size_t begin, big_size_t end, std::vector<T> vec);

template<typename RT, typename T>
RT shift_reduce_sum(big_size_t begin, big_size_t end, std::vector<T> vec);

// poor performance (i.e. not efficient)
template<typename RT, typename T>
RT pairwise_selection_sum(big_size_t begin, big_size_t end, std::vector<T> vec);

template<typename RT, typename T1, typename T2>
RT gcd(T1 a, T2 b);

/* return a merged samples' mean, variance and total size [2-samples].
 *
 * 	vec1d<RT> = {updated_t, updated_s, total_size}
 */
template<typename RT = float_auto, typename Size>
std::vector<RT> update_variance(RT t0, RT t1, RT s0, RT s1, Size size0,
		Size size1);

template<typename T>
T clip(T current_value, T min_value, T max_value);

template<typename T>
T sign(T value);
}

#endif /* SRC_ALGORITHM_HPP */
