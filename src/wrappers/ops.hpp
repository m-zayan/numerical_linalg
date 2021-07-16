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

template<typename T1, typename T2>
std::function<void(T1&, T2)> istatic_cast = [](T1 &v0, T2 v1) {

	v0 = static_cast<T1>(v1);
};

}

// ========================= nd::numeric::_h =======================

namespace nd::numeric::_h {

template<typename T1, typename T2>
using apply_func_t = std::function<
void(T1&, vec1d<max_size_t>&, vec1d<T2>&, max_size_t, max_size_t)>;

template<typename RT>
using wrapper_func_t11 = std::function<RT(vec1d<RT>&)>;

template<typename RT, typename T1, typename T2>
using wrapper_func_t12 = std::function<std::function<RT(T1)>(T2)>;

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
apply_func_t<vec1d<RT>, T> seq_var = [](vec1d<RT> &acc,
		vec1d<max_size_t> &indices, vec1d<T> &values, max_size_t begin,
		max_size_t end) {

	for (max_size_t i = begin; i < end; i++) {

		RT xi = static_cast<RT>(values[i]);

		acc[0] += xi;

		RT ssize = acc[2] + static_cast<RT>(i + 1);

		RT c = ssize * (ssize - 1.0);

		if (c != 0) {

			RT dev = (ssize * xi - acc[0]);

			acc[1] = acc[1] + (dev * dev) / c;
		}
	}

	acc[2] += (end - begin);
};

template<typename RT, typename T>
apply_func_t<vec1d<vec1d<RT>>, T> pair_var = [](vec1d<vec1d<RT>> &acc,
		vec1d<max_size_t> &indices, vec1d<T> &values, max_size_t begin,
		max_size_t end) {

	// initial <--> index = 1
	max_size_t index = acc[0][0];

	// sample-size
	max_size_t ssize = (end - begin);

	// compute | update <--> sample-variance
	seq_var<RT, T>(acc[index], indices, values, 0, ssize);

	// next
	acc[0][0]++;

	// values.size() == nd::mem:AUX_SIZE
	if (acc[0][0] > values.size()) {

		// reset index <--> merge
		acc[0][0] = 1;

		// reduced-flag
		acc[0][1] = 1;
	}
};

template<typename RT, typename T, typename pT>
wrapper_func_t12<RT, T, pT> pow = [](pT p) {

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

template<typename RT>
std::function<RT(vec1d<RT>&)> ppsum = [](vec1d<RT> &acc) {
	return algorithm::sum<RT>(0, acc.size(), acc.ref(0));
};

template<typename RT>
std::function<wrapper_func_t11<RT>(RT)> ppmean = [](RT size) {

	wrapper_func_t11<RT> wrapper_func = [size](vec1d<RT> &acc) {

		return algorithm::sum<RT>(0, acc.size(), acc.ref(0)) / size;
	};

	return wrapper_func;
};

template<typename RT>
std::function<RT(vec1d<RT>&)> ppseq_var = [](vec1d<RT> &acc) {

	return acc[1] / acc[2];
};

template<typename RT>
std::function<RT(vec1d<vec1d<RT>>&)> ppair_var = [](vec1d<vec1d<RT>> &acc) {

	std::function<vec1d<RT>(vec1d<RT>&, vec1d<RT>&)> uvar_wrapper = [](
			vec1d<RT> &nodei, vec1d<RT> &nodej) {

		return algorithm::update_variance(nodei[0], nodej[0], nodei[1],
				nodej[1], nodei[2], nodej[2]);
	};

	if (acc[0][1] == 1) {

		acc[1] = algorithm::reduce_pairwise<vec1d<RT>>(1, acc.size(),
				acc.ref(0), uvar_wrapper);
	}

	return acc[1][1] / acc[1][2];
};

template<typename RT>
std::function<RT(vec1d<RT>&)> ppseq_std = [](vec1d<RT> &acc) {

	RT sigma = ppseq_var<RT>(acc);

	return std::pow(sigma, 0.5);
};

template<typename RT>
std::function<RT(vec1d<vec1d<RT>>&)> ppair_std = [](vec1d<vec1d<RT>> &acc) {

	RT sigma = ppair_var<RT>(acc);

	return std::pow(sigma, 0.5);
};

}

#endif /* SRC_COMMON_WRAPPERS_HPP */
