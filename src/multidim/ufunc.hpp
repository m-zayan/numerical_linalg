/*
 * ufunc.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_MULTIDIM_UFUNC_HPP
#define SRC_MULTIDIM_UFUNC_HPP

//#include "../iterators/Pairwise.hpp"

#include "../iterators/Sequential.hpp"
#include "../iterators/PairwiseSequential.hpp"

#include "../iterators/RandomAccess.hpp"

#include "../wrappers/ops.hpp"

#include "../random/generator.hpp"

namespace _m_ops {

// [0] - lhs = rhs | d0 = func(d0, d1)
template<typename T1, typename T2>
void write_vec_vec(T1 *d0, T2 *d1, coords attr0, coords attr1,
		std::function<void(T1&, T1, T2)> func) {

	big_size_t size0 = attr0.size1d;
	big_size_t size1 = attr1.size1d;

	uflag8_t iter_type0 = attr0.iter_type;
	uflag8_t iter_type1 = attr1.iter_type;

	if (size0 != size1) {
		throw nd::exception("_m_ops::write_vec_vec(...), size must be same,\n\t"
				"attr0.size1d == attr1.size1d");
	}

	if (iter_type0 == 2 || iter_type1 == 2) {
		throw nd::exception("Invalid call for, _m_ops::write_vec_vec(...),\n\t"
				"attr0.iter_type = 2 || attr1.iter_type = 2");
	}

	// ==================================================================

	nd::iterator::Sequential iter0(attr0);
	nd::iterator::Sequential iter1(attr1);

	do {

		T1 *v0 = d0 + iter0.index();
		T2 *v1 = d1 + iter1.index();

		func(*v0, *v0, *v1);

	} while (iter0.next() && iter1.next());

}

// [1] - lhs = rhs | d = func(d, val)
template<typename T1, typename T2>
void write_val_vec(T1 *d, T2 val, coords attr,
		std::function<void(T1&, T1, T2)> func) {

	uflag8_t iter_type = attr.iter_type;

	if (iter_type == 2) {
		throw nd::exception("Invalid call for, _m_ops::write_val_vec(...),\n\t"
				"attr.iter_type = 2");
	}

	// ==================================================================

	nd::iterator::Sequential iter(attr);

	do {

		T1 *v = d + iter.index();

		func(*v, *v, val);

	} while (iter.next());
}

/* [2] - lhs = rhs | res = d | use-case -> type-casting
 *
 * broadcastable (i.e. repeat)
 */
template<typename RT, typename T>
void copy(RT *res, T *d, coords attr, coords out_attr) {

	big_size_t size = attr.size1d;
	big_size_t out_size = out_attr.size1d;

	uflag8_t iter_type = attr.iter_type;
	uflag8_t out_iter_type = out_attr.iter_type;

	if (size != out_size) {
		throw nd::exception("_m_ops::copy(...), size must be same,\n\t"
				"attr.size1d  != out_attr.size1d");
	}

	if (iter_type == 2) {
		throw nd::exception("Invalid call for, _m_ops::copy(...),\n\t"
				"attr.iter_type = 2");
	}

	if (out_iter_type == 1) {
		throw nd::exception("Invalid call for, _m_ops::copy(...),\n\t"
				"out_attr.iter_type = 1");
	}

	// ==================================================================

	if (out_iter_type == 0) {

		nd::iterator::Sequential iter(attr);
		big_size_t i = 0;

		do {

			res[i++] = static_cast<RT>(d[iter.index()]);

		} while (iter.next());

	}

	else {

		nd::iterator::PairwiseSequential pseqIter(attr, out_attr);

		do {

			res[pseqIter.index(2)] = static_cast<RT>(d[pseqIter.index(0)]);

		} while (pseqIter.next());
	}

}

/* [3] - lhs = rhs | res = func(d, val) | ex. use-case -> boolean function
 *
 * broadcastable (i.e. repeat)
 */
template<typename RT, typename T1, typename T2>
void write_vec_val_vec(RT *res, T1 *d, T2 val, coords attr, coords out_attr,
		std::function<void(RT&, T1, T2)> func) {

	big_size_t size = attr.size1d;
	big_size_t out_size = out_attr.size1d;

	uflag8_t iter_type = attr.iter_type;
	uflag8_t out_iter_type = out_attr.iter_type;

	if (size != out_size) {
		throw nd::exception(
				"_m_ops::write_vec_val_vec(...), size must be same, "
						"attr.size1d  != out_attr.size1d");
	}

	if (iter_type == 2) {
		throw nd::exception("Invalid call for, _m_ops::write_vec_val_vec(...), "
				"RHS: coords::iter_type = 2");
	}

	if (out_iter_type == 1) {
		throw nd::exception(
				"Invalid call for, _m_ops::write_vec_val_vec(...),\n\t"
						"out_attr.iter_type = 1");
	}

	// ==================================================================

	if (out_iter_type == 0) {

		nd::iterator::Sequential iter(attr);

		big_size_t i = 0;

		do {

			T1 *v = d + iter.index();

			func(res[i++], *v, val);

		} while (iter.next());

	}

	else {

		nd::iterator::PairwiseSequential pseqIter(attr, out_attr);

		do {

			T1 *v = d + pseqIter.index(0);

			func(res[pseqIter.index(2)], *v, val);

		} while (pseqIter.next());
	}

}

/* [4] - lhs = rhs | res = func(d0, d1) | ex. use-case -> boolean function
 *
 * broadcastable
 */
template<typename RT, typename T1, typename T2>
void write_vec_vec_vec(RT *res, T1 *d0, T2 *d1, coords attr0, coords attr1,
		coords out_attr, std::function<void(RT&, T1, T2)> func) {

	big_size_t size0 = attr0.size1d;
	big_size_t size1 = attr1.size1d;

	big_size_t out_size = out_attr.size1d;

	uflag8_t out_iter_type = out_attr.iter_type;

	if (out_iter_type == 1) {
		throw nd::exception("Invalid call for, _m_ops::write_vec_vec_vec(...), "
				"LHS: coords::iter_type = 1");
	}

	if (out_iter_type == 0 && (size0 != size1 || out_size != size0)) {

		throw nd::exception("_m_ops::write_vec_vec(...), size must be same, "
				"attr0.size1d == attr1.size1d, out_attr.iter_type = 0");
	}

	// ==================================================================

	// case: 0  (i.e. no broadcast)
	if (out_iter_type == 0) {

		nd::iterator::Sequential iter0(attr0);
		nd::iterator::Sequential iter1(attr1);

		big_size_t i = 0;

		do {

			T1 *v0 = d0 + iter0.index();
			T2 *v1 = d1 + iter1.index();

			func(res[i++], *v0, *v1);

		} while (iter0.next() && iter1.next());
	}

	else {

		nd::iterator::PairwiseSequential pseqIter(attr0, attr1);

		do {

			T1 *v0 = d0 + pseqIter.index(0);
			T2 *v1 = d1 + pseqIter.index(1);

			func(res[pseqIter.index(2)], *v0, *v1);

		} while (pseqIter.next());
	}
}

// [5] - lhs = rhs | res = func(d0)
template<typename RT, typename T>
void write_vec(RT *res, T *d, coords attr, std::function<RT(T)> func) {

	if (attr.iter_type == 2) {

		throw nd::exception("Invalid call for, _m_ops::write_vec(...), "
				"coords::iter_type = 2");
	}

	nd::iterator::Sequential iter(attr);

	big_size_t i = 0;

	do {

		res[i++] = func(d[iter.index()]);

	} while (iter.next());
}

}

#endif /* SRC_MULTIDIM_UFUNC_HPP */
