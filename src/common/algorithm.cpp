/*
 * algorithms.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./algorithm.hpp"

template<typename RT, typename T>
RT algorithm::_h::naive_summation(big_size_t begin, big_size_t end, T *x) {

	RT sum = 0;

	for (big_size_t i = begin; i < end; i++) {
		sum += x[i];
	}

	return sum;
}

template<typename RT, typename T>
RT algorithm::_h::pairwise_summation(big_size_t begin, big_size_t end, T *x) {

	big_size_t n = (end - begin);

	if (n <= 64) {
		return algorithm::_h::naive_summation<RT>(begin, end, x);
	}

	else {
		// big_size_t mid = n/2
		return algorithm::_h::pairwise_summation<RT>(begin, n / 2, x)
				+ algorithm::_h::pairwise_summation<RT>(begin, n - n / 2,
						x + n / 2);
	}
}

// Naive summation
template<typename RT, typename T>
RT algorithm::naive_summation(big_size_t begin, big_size_t end,
		std::vector<T> vec) {
	return algorithm::_h::naive_summation<RT>(begin, end, &vec[0]);
}

/* Kahan summation, worst-case error that grows
 * proportional to n = (end - begin) - O(nε), and sqrt(n)
 * for random input (Random walk).
 */
template<typename RT, typename T>
RT algorithm::kahan_summation(big_size_t begin, big_size_t end,
		std::vector<T> vec) {

	RT sum = 0;
	RT c = 0;

	for (big_size_t i = begin; i < end; i++) {

		RT r = vec[i] + c;
		RT sum_next = sum + r;

		c = r - (sum_next - sum);
		sum = sum_next;
	}

	return sum;
}

/* Pairwise summation, worst-case error that grows, by O(log2(n))
 * where n is the sequence length.
 */
template<typename RT, typename T>
RT algorithm::pairwise_summation(big_size_t begin, big_size_t end,
		std::vector<T> vec) {

	return algorithm::_h::pairwise_summation<RT>(begin, end, &vec[begin]);
}

/*
 * Modified version of pairwise summation (shift reduce sum),
 * dicussed by Barnaby Dalton, Amy Wang, Bob Blainey
 * https://dl.acm.org/doi/pdf/10.1145/2568058.2568070?download=true
 */
template<typename RT, typename T>
RT algorithm::shift_reduce_sum(big_size_t begin, big_size_t end,
		std::vector<T> vec) {

	std::vector<RT> memory(64);
	min_size_t xi = 0;

	RT sum = 0;

	for (big_size_t i = begin; i < end; i++) {

		RT v = vec[i];

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
 * Comparatively large constant factor: T(n) = 32 * log2(64) * n
 */
template<typename RT, typename T>
RT algorithm::pairwise_selection_sum(big_size_t begin, big_size_t end,
		std::vector<T> vec) {

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
		memory.push(x1 + x2);

		/* if queue size (memory) exceeds - MAX_EXTRA_SPACE,
		 * reduce memory size, (i.e. repeat pair-wise selelction)
		 */
		if (memory.size() > MAX_EXTRA_SPACE) {

			while (memory.size() > 1) {

				x1 = memory.next();
				x2 = memory.next();

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

		x1 = memory.next();
		x2 = memory.next();

		memory.push(x1 + x2);
	}

	return memory.front();
}

template<typename RT, typename T1, typename T2>
RT algorithm::gcd(T1 a, T2 b) {

	if (b == 0)
		return a;

	return gcd(b, a % b);
}

/*
 * Updating Formulae and a Pairwise Algorithm for Computing Sample Variances:
 *
 * 		http://i.stanford.edu/pub/cstr/reports/cs/tr/79/773/CS-TR-79-773.pdf
 */
template<typename RT, typename Size>
std::vector<RT> algorithm::update_variance(RT mean0, RT mean1, RT var0, RT var1,
		Size size0, Size size1) {

	RT m = static_cast<RT>(size0);
	RT n = static_cast<RT>(size1);

	RT c0 = m / (n * (m + n));
	RT c1 = (m + n) / m;

	RT mean_diff = (c1 * mean0 - mean1);

	RT uvar = var0 + var1 + (c0 * mean_diff * mean_diff);

	std::vector<RT> updated = { mean0 + mean1, uvar, n + m };

	return updated;
}

