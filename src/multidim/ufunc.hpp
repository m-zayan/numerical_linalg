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
std::function<T(vipair<T>)> ppvalue = [](vipair<T> acc) {

	return static_cast<RT>(acc.first);
};

template<typename RT, typename T>
std::function<RT(vipair<T>)> ppindex = [](vipair<T> acc) {
	return static_cast<RT>(acc.second);
};

template<typename RT>
std::function<RT(vec1d<RT>)> v_sum = [](vec1d<RT> acc) {
	return acc.sum(0, acc.size());
};

}  // namespace nd::numeric::_h

#endif /* SRC_MULTIDIM_UFUNC_HPP */
