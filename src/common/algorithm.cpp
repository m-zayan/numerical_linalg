/*
 * algorithms.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./algorithm.hpp"

template<typename T>
algorithm<T>::algorithm() = default;

// protected: static T __naive summation
template<typename T>
T algorithm<T>::__naive_summation(big_size_t begin, big_size_t end, T *x) {

	T sum = 0;

	for (big_size_t i = begin; i < end; i++) {
		sum += x[i];
	}

	return sum;
}

// Naive summation
template<typename T>
T algorithm<T>::naive_summation(big_size_t begin, big_size_t end,
		std::vector<T> vec) {
	return __naive_summation(begin, end, &vec[0]);
}

/* Kahan summation, worst-case error that grows
 * proportional to n = (end - begin) - O(nε), and sqrt(n)
 * for random input (Random walk).
 */
template<typename T>
T algorithm<T>::kahan_summation(big_size_t begin, big_size_t end,
		std::vector<T> vec) {

	T sum = 0;
	T c = 0;

	for (big_size_t i = begin; i < end; i++) {
		T r = vec[i] + c;
		T sum_next = sum + r;

		c = r - (sum_next - sum);
		sum = sum_next;
	}

	return sum;
}

/*
 * protected: static T __pairwise summation
 */
template<typename T>
T algorithm<T>::__pairwise_summation(big_size_t begin, big_size_t end, T *x) {

	big_size_t n = (end - begin);

	if (n <= 64) {
		return __naive_summation(begin, end, x);
	}

	else {
		// big_size_t mid = n/2
		return __pairwise_summation(begin, n / 2, x)
				+ __pairwise_summation(begin, n - n / 2, x + n / 2);
	}
}

/* Pairwise summation, worst-case error that grows, by O(log2(n))
 * where n is the sequence length.
 */
template<typename T>
T algorithm<T>::pairwise_summation(big_size_t begin, big_size_t end,
		std::vector<T> vec) {

	return __pairwise_summation(begin, end, &vec[begin]);
}

/*
 * Modified version of pairwise summation (shift reduce sum),
 * dicussed by Barnaby Dalton, Amy Wang, Bob Blainey
 * https://dl.acm.org/doi/pdf/10.1145/2568058.2568070?download=true
 */
template<typename T>
T algorithm<T>::shift_reduce_sum(big_size_t begin, big_size_t end,
		std::vector<T> vec) {

	std::vector<T> memory(64);
	min_size_t xi = 0;

	T sum = 0;

	for (big_size_t i = begin; i < end; i++) {

		T v = vec[i];

		for (big_size_t j = 1; (i - begin) & j; j <<= 1, --xi) {
			v += memory[xi - 1];
		}
		memory[xi++] = v;
	}

	while (xi) {
		sum += memory[--xi];
	}

	return sum;
}

/*
 * MAX_EXTRA_SPACE = 64
 *
 * Time Complexity: O(n)
 * Space Complexity: O(MAX_EXTRA_SPACE) - Auxiliary Space, for n >= MAX_EXTRA_SPACE
 *
 * Very large constant factor: T(n) = 32 * log2(64) * n
 */
template<typename T>
T algorithm<T>::pairwise_selection_sum(big_size_t begin, big_size_t end,
		std::vector<T> vec) {

	/*
	 * Error reduction is proportional to MAX_EXTRA_SPACE,
	 * such that, best case error (nearly, pairwise sum result)
	 * at MAX_EXTRA_SPACE = n/2 + 1, in other words,
	 * if(memory.size() > MAX_EXTRA_SPACE), is always false
	 */
	min_size_t MAX_EXTRA_SPACE = 64;

	big_size_t size = end - begin;
	big_size_t n_step = end - begin - ((end - begin) % 2);

	big_size_t start = begin;

	std::queue<T> memory;

	while (start < n_step) {

		// select pairs
		T x1 = vec[start];
		T x2 = vec[start + 1];

		start += 2;

		// sum
		memory.push(x1 + x2);

		/* if queue size (memory) exceeds - MAX_EXTRA_SPACE,
		 * reduce memory size, (i.e. repeat pair-wise selelction)
		 */
		if (memory.size() > MAX_EXTRA_SPACE) {

			while (memory.size() > 1) {

				T x1 = memory.front();
				memory.pop();

				T x2 = memory.front();
				memory.pop();

				memory.push(x1 + x2);
			}
		}
	}

	// odd size
	if (size % 2) {
		memory.push(vec[start]);
	}

	// repeat-pair-wise selelction | neglected
	while (memory.size() > 1) {

		T x1 = memory.front();
		memory.pop();

		T x2 = memory.front();
		memory.pop();

		memory.push(x1 + x2);
	}

	return memory.front();
}

template<typename T>
algorithm<T>::~algorithm() {
}
