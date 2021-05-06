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

template<typename RT, typename T1, typename T2>
using wrapper_func_t = std::function<std::function<RT(T1)>(T2)>;

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

template<typename RT, typename T, typename pT>
wrapper_func_t<RT, T, pT> pow = [](pT p) {

	std::function<RT(T)> wrapper_func = [p](T value) {

		return std::pow(value, p);
	};

	return wrapper_func;
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
	return algorithm::sum<RT>(0, acc.size(), acc.ref(0));
};

}

#endif /* SRC_COMMON_WRAPPERS_HPP */
