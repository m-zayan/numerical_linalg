/*
 * ufunc.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_MULTIDIM_UFUNC_HPP
#define SRC_MULTIDIM_UFUNC_HPP

#include "../iterators/RandomAccess.hpp"

namespace _m_ops {

// [0] - lhs = rhs | d0 = func(d0, d1)
template<typename T1, typename T2>
void write_vec_vec(T1 *d0, T2 *d1, coords attr0, coords attr1,
		std::function<void(T1&, T1, T2)> func, bool req_iter0, bool req_iter1) {

	big_size_t size0 = attr0.size1d;
	big_size_t size1 = attr1.size1d;

	if (size0 != size1) {

		throw nd::exception("_m_write_vec_vec, size should be same, "
				"attr0.size1d == attr1.size1d");
	}

	if (req_iter0 && req_iter1) {

		nd::iterator::RandomAccess rndIter0(attr0);
		nd::iterator::RandomAccess rndIter1(attr1);

		for (big_size_t i = 0; i < size0; i++) {

			T1 *v0 = d0 + rndIter0.index_at(i);
			T2 *v1 = d1 + rndIter1.index_at(i);

			func(*v0, *v0, *v1);
		}
	}

	else if (req_iter0) {

		nd::iterator::RandomAccess rndIter0(attr0);

		for (big_size_t i = 0; i < size0; i++) {

			T1 *v0 = d0 + rndIter0.index_at(i);
			T2 *v1 = d1 + i;

			func(*v0, *v0, *v1);
		}
	}

	else if (req_iter1) {

		nd::iterator::RandomAccess rndIter1(attr1);

		for (big_size_t i = 0; i < size0; i++) {

			T1 *v0 = d0 + i;
			T2 *v1 = d1 + rndIter1.index_at(i);

			func(*v0, *v0, *v1);
		}
	}

	else {

		for (big_size_t i = 0; i < size0; i++) {

			T1 *v0 = d0 + i;
			T2 *v1 = d1 + i;

			func(*v0, *v0, *v1);
		}
	}
}

// [1] - lhs = rhs | d = func(d, val)
template<typename T1, typename T2>
void write_val_vec(T1 *d, T2 val, coords attr,
		std::function<void(T1&, T1, T2)> func, bool req_iter) {

	big_size_t size = attr.size1d;

	if (req_iter) {

		nd::iterator::RandomAccess rndIter(attr);

		for (big_size_t i = 0; i < size; i++) {

			T1 *v = d + rndIter.index_at(i);

			func(*v, *v, val);
		}
	}

	else {

		for (big_size_t i = 0; i < size; i++) {

			T1 *v = d + i;

			func(*v, *v, val);
		}
	}

}

// [2] - lhs = rhs | res = d | use-case -> type-casting
template<typename RT, typename T>
void copy(RT *res, T *d, coords attr, bool req_iter) {

	big_size_t size = attr.size1d;

	if (req_iter) {

		nd::iterator::RandomAccess rndIter(attr);

		for (big_size_t i = 0; i < size; i++) {

			res[i] = d[rndIter.index_at(i)];
		}
	}

	else {

		for (big_size_t i = 0; i < size; i++) {

			res[i] = d[i];
		}
	}

}

// [3] - lhs = rhs | res = func(d, val) | ex. use-case -> boolean function
template<typename RT, typename T1, typename T2>
void write_vec_val_vec(RT *res, T1 *d, T2 val, coords attr,
		std::function<void(RT&, T1, T2)> func, bool req_iter) {

	big_size_t size = attr.size1d;

	if (req_iter) {

		nd::iterator::RandomAccess rndIter(attr);

		for (big_size_t i = 0; i < size; i++) {

			T1 *v = d + rndIter.index_at(i);

			func(res[i], *v, val);
		}
	}

	else {

		for (big_size_t i = 0; i < size; i++) {

			T1 *v = d + i;

			func(res[i], *v, val);
		}
	}

}

// [4] - lhs = rhs | res = func(d0, d1) | ex. use-case -> boolean function
template<typename RT, typename T1, typename T2>
void write_vec_vec_vec(RT *res, T1 *d0, T2 *d1, coords attr0, coords attr1,
		std::function<void(RT&, T1, T2)> func, bool req_iter0, bool req_iter1) {

	big_size_t size0 = attr0.size1d;
	big_size_t size1 = attr1.size1d;

	if (size0 != size1) {

		throw nd::exception("_m_write_vec_vec, size should be same, "
				"attr0.size1d == attr1.size1d");
	}

	if (req_iter0 && req_iter1) {

		nd::iterator::RandomAccess rndIter0(attr0);
		nd::iterator::RandomAccess rndIter1(attr1);

		for (big_size_t i = 0; i < size0; i++) {

			T1 *v0 = d0 + rndIter0.index_at(i);
			T2 *v1 = d1 + rndIter1.index_at(i);

			func(res[i], *v0, *v1);
		}
	}

	else if (req_iter0) {

		nd::iterator::RandomAccess rndIter0(attr0);

		for (big_size_t i = 0; i < size0; i++) {

			T1 *v0 = d0 + rndIter0.index_at(i);
			T2 *v1 = d1 + i;

			func(res[i], *v0, *v1);
		}
	}

	else if (req_iter1) {

		nd::iterator::RandomAccess rndIter1(attr1);

		for (big_size_t i = 0; i < size0; i++) {

			T1 *v0 = d0 + i;
			T2 *v1 = d1 + rndIter1.index_at(i);

			func(res[i], *v0, *v1);
		}
	}

	else {

		for (big_size_t i = 0; i < size0; i++) {

			T1 *v0 = d0 + i;
			T2 *v1 = d1 + i;

			func(res[i], *v0, *v1);
		}
	}
}
}

namespace nd::numeric::_h {

template<typename T1, typename T2>
using apply_func_t = std::function<
void(T1&, vec1d<max_size_t>&, vec1d<T2>&, max_size_t, max_size_t)>;

/*
 * pair of vec1d:
 *
 * {max_size_t --> min-clipped-size, max-clipped-size,
 * 			max_size_t --> current-index}
 */
template<typename T>
using ppveci = std::pair<vec1d<vec1d<T>>, vec1d<max_size_t>>;

// func
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
apply_func_t<ppveci<RT>, T> var = [](ppveci<RT> &acc,
		vec1d<max_size_t> &indices, vec1d<T> &values, max_size_t begin,
		max_size_t end) {

	max_size_t n = end - begin;

	RT ssize = static_cast<RT>(n);

	RT sum = values.sum(0, n);
	RT mean = sum * (1.0 / ssize);

	vec1d<RT> tmp(n);

	for (max_size_t i = begin; i < end; i++) {

		tmp[i] = (values[i] - mean);
		tmp[i] *= tmp[i];
	}

	RT var = tmp.sum(0, n) * (1.0 / ssize);

	if (acc.second[2] >= acc.first[0].size()) {

		// Debugging
		throw nd::exception("Variance Accumulator, Index Out of Range,"
				" nd::numeric::_h::var(...)");
	}

	// sample mean
	acc.first[0][acc.second[2]] = mean;

	// sample variance
	acc.first[1][acc.second[2]] = var;

	acc.second[0] = std::min(acc.second[0], n);
	acc.second[1] = std::max(acc.second[1], n);

	acc.second[2]++;
};

// ppfunc
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
std::function<vec1d<RT>(RT, RT, RT, RT, RT, RT)> update_var_step = [](RT mean0,
		RT mean1, RT var0, RT var1, RT m, RT n) {

	RT c0 = m / (n * (m + n));
	RT c1 = (m + n) / m;

	RT mean_diff = (c1 * mean0 - mean1);

	RT uvar = var0 + var1 + (c0 * mean_diff * mean_diff);

	vec1d<RT> updated = { mean0 + mean1, uvar };

	return updated;

};

template<typename RT>
std::function<
		max_size_t(vec1d<std::queue<RT>> &memory, RT &m, RT &n,
				max_size_t n_steps)> update_var_n_steps = [](
		vec1d<std::queue<RT>> &memory, RT &m, RT &n, max_size_t n_steps) {

	RT mean0, mean1, var0, var1;

	vec1d<RT> updated;

	for (max_size_t i = 0; i < n_steps / 2; i++) {

		mean0 = memory[0].front();

		memory[0].pop();

		mean1 = memory[0].front();

		memory[0].pop();

		var0 = memory[1].front();

		memory[1].pop();

		var1 = memory[1].front();

		memory[1].pop();

		if (i == n_steps - 1) {

			updated = nd::numeric::_h::update_var_step<RT>(mean0, mean1, var0,
					var1, m, n);
		}

		else {

			updated = nd::numeric::_h::update_var_step<RT>(mean0, mean1, var0,
					var1, m, m);
		}

		memory[0].push(updated[0]);
		memory[1].push(updated[1]);
	}

	m *= 2;
	n = n + m;

	return n_steps / 2;
};

template<typename RT>
std::function<RT(ppveci<RT>&)> update_variance = [](ppveci<RT> &acc) {

	max_size_t n_splits = acc.first[0].size();

	max_size_t size0 = acc.second[0];
	max_size_t size1 = acc.second[1];

	RT m = static_cast<RT>(size0);
	RT n = static_cast<RT>(size1);

	vec1d<std::queue<RT>> memory(2);

	max_size_t n_steps = n_splits / 2;

	for (max_size_t i = 0; i < n_steps; i += 2) {

		memory[0].push(acc.first[0][i]);
		memory[0].push(acc.first[0][i + 1]);

		memory[1].push(acc.first[1][i]);
		memory[1].push(acc.first[1][i + 1]);
	}

	while (n_steps > 1) {

		n_steps = nd::numeric::_h::update_var_n_steps<RT>(memory, m, n,
				n_steps);
	}

	if (n_splits % 2) {

		memory[0].push(acc.first[0][n_splits - 1]);
		memory[1].push(acc.first[1][n_splits - 1]);

		n_steps = nd::numeric::_h::update_var_n_steps<RT>(memory, m, n,
				n_steps);
	}

	return memory[1].front();
};

}  // namespace nd::numeric::_h

#endif /* SRC_MULTIDIM_UFUNC_HPP */
