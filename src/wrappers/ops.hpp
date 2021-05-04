/*
 * wrappers.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_COMMON_WRAPPERS_HPP
#define SRC_COMMON_WRAPPERS_HPP

#include "../typing/types.hpp"

// algorithm.hpp --> #include "../handlers/exception.hpp"
#include "./algorithm.hpp"

// ========================= _v_ops  =======================

namespace _v_ops {

template<typename RT, typename T1, typename T2>
std::function<void(RT&, T1, T2)> mul = [](RT &v0, T1 v1, T2 v2) {

	v0 = v1 * v2;
};

template<typename RT, typename T1, typename T2>
std::function<void(RT&, T1, T2)> div = [](RT &v0, T1 v1, T2 v2) {

	v0 = v1 / v2;
};

template<typename RT, typename T1, typename T2>
std::function<void(RT&, T1, T2)> add = [](RT &v0, T1 v1, T2 v2) {

	v0 = v1 + v2;
};

template<typename RT, typename T1, typename T2>
std::function<void(RT&, T1, T2)> sub = [](RT &v0, T1 v1, T2 v2) {

	v0 = v1 - v2;
};

template<typename RT, typename T1, typename T2>
std::function<void(RT&, T1, T2)> bool_equal = [](RT &v0, T1 v1, T2 v2) {

	v0 = (v1 == v2);
};

}

// ========================= nd::numeric::_h =======================

namespace nd::numeric::_h {

template<typename T1, typename T2>
using apply_func_t = std::function<
void(T1&, vec1d<max_size_t>&, vec1d<T2>&, max_size_t, max_size_t)>;

template<typename T>
apply_func_t<vipair<T>, T> maximum = [](vipair<T> &acc,
		vec1d<max_size_t> &indices, vec1d<T> &values, max_size_t begin,
		max_size_t end) {

	for (max_size_t i = begin; i < end; i++) {

		if (acc.first == values[i])
			continue;

		acc = std::max(acc, { values[i], indices[i] });
	}

};

template<typename T>
apply_func_t<vipair<T>, T> minimum = [](vipair<T> &acc,
		vec1d<max_size_t> &indices, vec1d<T> &values, max_size_t begin,
		max_size_t end) {

	for (max_size_t i = begin; i < end; i++) {

		if (acc.first == values[i])
			continue;

		acc = std::min(acc, { values[i], indices[i] });
	}

};

template<typename RT, typename T>
apply_func_t<vec1d<RT>, T> sum = [](vec1d<RT> &acc, vec1d<max_size_t> &indices,
		vec1d<T> &values, max_size_t begin, max_size_t end) {

	for (max_size_t i = begin; i < end; i++) {
		acc[i] += static_cast<RT>(values[i]);
	}
};

template<typename RT, typename T>
apply_func_t<vec1d_args_wrapper<RT>, T> var = [](vec1d_args_wrapper<RT> &acc,
		vec1d<max_size_t> &indices, vec1d<T> &values, max_size_t begin,
		max_size_t end) {

	max_size_t n = end - begin;

	RT ssize = static_cast<RT>(n);

	RT sum = algorithm::sum<RT>(0, n, values.ref(0));
	RT mean = sum * (1.0 / ssize);

	vec1d<RT> tmp(n);

	for (max_size_t i = begin; i < end; i++) {

		tmp[i] = (values[i] - mean);
		tmp[i] *= tmp[i];
	}

	RT var = algorithm::sum<RT>(0, n, tmp.ref(0)) * (1.0 / ssize);

	if (acc.first >= acc.second.size()) {

		// Debugging
		throw nd::exception("Variance Accumulator, Index Out of Range,"
				" nd::numeric::_h::var(...)");
	}

	// sample sum
	acc.second[acc.first][0] = sum;

	// sample variance
	acc.second[acc.first][1] = var;

	// sample size
	acc.second[acc.first][2] = ssize;

	acc.first++;

};

// ppfunc (post-processing-functions)

template<typename RT, typename T>
std::function<T(vipair<T>&)> ppvalue = [](vipair<T> &acc) {

	return static_cast<RT>(acc.first);
};

template<typename RT, typename T>
std::function<RT(vipair<T>&)> ppindex = [](vipair<T> &acc) {
	return static_cast<RT>(acc.second);
};

template<typename RT, typename T>
std::function<RT(pair_of<T>&)> pfirst = [](pair_of<T> &acc) {
	return static_cast<RT>(acc.first);
};

template<typename RT, typename T>
std::function<RT(pair_of<T>&)> psecond = [](pair_of<T> &acc) {
	return static_cast<RT>(acc.second);
};

template<typename RT>
std::function<RT(vec1d<RT>&)> v_sum = [](vec1d<RT> &acc) {
	return acc.sum(0, acc.size());
};

template<typename RT>
std::function<RT(vec1d_args_wrapper<RT>&)> update_variance = [](
		vec1d_args_wrapper<RT> &acc) {

	max_size_t n_splits = acc.second.size();

	/*
	 * v0[i] = {mean_i, var_i, size_i}
	 * v1[j] = {mean_j, var_j, size_j}
	 */
	std::function<vec1d<RT>(vec1d<RT>&, vec1d<RT>&)> reduce_wrapper = [](
			vec1d<RT> &v0, vec1d<RT> &v1) {

		RT sum0 = v0[0];
		RT sum1 = v1[0];

		RT var0 = v0[1];
		RT var1 = v1[1];

		RT size0 = v0[2];
		RT size1 = v1[2];

		vec1d<RT> updated = algorithm::update_variance(sum0, sum1, var0, var1,
				size0, size1);

		return updated;
	};

	vec1d<RT> updated_total = algorithm::reduce_pairwise_selection(0, n_splits,
			acc.second, reduce_wrapper);

	return updated_total[1];

};
}

#endif /* SRC_COMMON_WRAPPERS_HPP */
