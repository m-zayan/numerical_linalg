/*
 * ufunc.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_MULTIDIM_UFUNC_HPP
#define SRC_MULTIDIM_UFUNC_HPP

#include "../iterators/Pairwise.hpp"
#include "../wrappers/ops.hpp"

#include "../random/generator.cpp"

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

	nd::iterator::RandomAccess rndIter0(attr0);
	nd::iterator::RandomAccess rndIter1(attr1);

	for (big_size_t i = 0; i < size0; i++) {

		T1 *v0 = d0 + rndIter0.index_at(i);
		T2 *v1 = d1 + rndIter1.index_at(i);

		func(*v0, *v0, *v1);
	}

}

// [1] - lhs = rhs | d = func(d, val)
template<typename T1, typename T2>
void write_val_vec(T1 *d, T2 val, coords attr,
		std::function<void(T1&, T1, T2)> func) {

	big_size_t size = attr.size1d;

	uflag8_t iter_type = attr.iter_type;

	if (iter_type == 2) {
		throw nd::exception("Invalid call for, _m_ops::write_val_vec(...),\n\t"
				"attr.iter_type = 2");
	}

	// ==================================================================

	nd::iterator::RandomAccess rndIter(attr);

	for (big_size_t i = 0; i < size; i++) {

		T1 *v = d + rndIter.index_at(i);

		func(*v, *v, val);
	}
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

		nd::iterator::RandomAccess rndIter(attr);

		for (big_size_t i = 0; i < size; i++) {

			res[i] = static_cast<RT>(d[rndIter.index_at(i)]);
		}

	}

	else {

		nd::iterator::Pairwise pIter(attr, out_attr);

		for (big_size_t i = 0; i < out_size; i++) {

			res[pIter.index_at(i, 2)] =
					static_cast<RT>(d[pIter.index_at(i, 0)]);
		}
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

		nd::iterator::RandomAccess rndIter(attr);

		for (big_size_t i = 0; i < size; i++) {

			T1 *v = d + rndIter.index_at(i);

			func(res[i], *v, val);
		}

	}

	else {

		nd::iterator::Pairwise pIter(attr, out_attr);

		for (big_size_t i = 0; i < out_size; i++) {

			T1 *v = d + pIter.index_at(i, 0);

			func(res[pIter.index_at(i, 2)], *v, val);
		}
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

		nd::iterator::RandomAccess rndIter0(attr0);
		nd::iterator::RandomAccess rndIter1(attr1);

		for (big_size_t i = 0; i < size0; i++) {

			T1 *v0 = d0 + rndIter0.index_at(i);
			T2 *v1 = d1 + rndIter1.index_at(i);

			func(res[i], *v0, *v1);
		}
	}

	else {

		nd::iterator::Pairwise pIter(attr0, attr1);

		for (big_size_t i = 0; i < out_size; i++) {

			T1 *v0 = d0 + pIter.index_at(i, 0);
			T2 *v1 = d1 + pIter.index_at(i, 1);

			func(res[pIter.index_at(i, 2)], *v0, *v1);
		}
	}
}

// [5] - lhs = rhs | res = func(d0)
template<typename RT, typename T>
void write_vec(RT *res, T *d, coords attr, std::function<RT(T)> func) {

	big_size_t size = attr.size1d;

	if (attr.iter_type == 2) {

		throw nd::exception("Invalid call for, _m_ops::write_vec(...), "
				"coords::iter_type = 2");
	}

	nd::iterator::RandomAccess rndIter(attr);

	for (big_size_t i = 0; i < size; i++) {

		res[i] = func(d[rndIter.index_at(i)]);
	}
}

}

#endif /* SRC_MULTIDIM_UFUNC_HPP */
