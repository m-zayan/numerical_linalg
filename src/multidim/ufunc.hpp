/*
 * ufunc.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_MULTIDIM_UFUNC_HPP
#define SRC_MULTIDIM_UFUNC_HPP

//#include "../iterators/Pairwise.hpp"
//#include "../iterators/Sequential.hpp"

#include "../iterators/factory.hpp"
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

	if (size0 != size1) {
		throw nd::exception("_m_ops::write_vec_vec(...), size must be same,\n\t"
				"attr0.size1d == attr1.size1d");
	}

	// ==================================================================

	// [0]
	nd::iterator::Iterator *iter0 = nd::iterator::init_iterator(attr0);
	nd::iterator::Iterator *iter1 = nd::iterator::init_iterator(attr1);

	do {

		T1 *v0 = d0 + iter0->index();
		T2 *v1 = d1 + iter1->index();

		func(*v0, *v0, *v1);

	} while (iter0->next() && iter1->next());

	// [1]
	nd::iterator::free_iterator(iter0);
	nd::iterator::free_iterator(iter1);

}

// [1] - lhs = rhs | d = func(d, val)
template<typename T1, typename T2>
void write_val_vec(T1 *d, T2 val, coords attr,
		std::function<void(T1&, T1, T2)> func) {

	// [0]
	nd::iterator::Iterator *iter = nd::iterator::init_iterator(attr);

	do {

		T1 *v = d + iter->index();

		func(*v, *v, val);

	} while (iter->next());

	// [1]
	nd::iterator::free_iterator(iter);
}

/* [2] - lhs = rhs | res = d | use-case -> type-casting
 *
 * broadcastable (i.e. repeat)
 */
template<typename RT, typename T>
void copy(RT *res, T *d, coords attr, coords out_attr) {

	big_size_t size = attr.size1d;
	big_size_t out_size = out_attr.size1d;

	if (size != out_size) {
		throw nd::exception("_m_ops::copy(...), size must be same,\n\t"
				"attr.size1d  != out_attr.size1d");
	}

	if (require_linear_iterator(out_attr)) {

		throw nd::exception("Invalid call for, _m_ops::copy(...),\n\t"
				"require_linear_iterator(...)");
	}

	// ==================================================================

	if (require_no_iterator(out_attr)) {

		// [0]
		nd::iterator::Iterator *iter = nd::iterator::init_iterator(attr);

		big_size_t i = 0;

		do {

			res[i++] = static_cast<RT>(d[iter->index()]);

		} while (iter->next());

		// [1]
		nd::iterator::free_iterator(iter);

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

	if (size != out_size) {
		throw nd::exception(
				"_m_ops::write_vec_val_vec(...), size must be same,\n\t"
						"attr.size1d  != out_attr.size1d");
	}

	if (require_linear_iterator(out_attr)) {
		throw nd::exception(
				"Invalid call for, _m_ops::write_vec_val_vec(...),\n\t"
						"require_linear_iterator(...)");
	}

	// ==================================================================

	if (require_no_iterator(out_attr)) {

		// [0]
		nd::iterator::Iterator *iter = nd::iterator::init_iterator(attr);

		big_size_t i = 0;

		do {

			T1 *v = d + iter->index();

			func(res[i++], *v, val);

		} while (iter->next());

		// [1]
		nd::iterator::free_iterator(iter);

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

	if (require_linear_iterator(out_attr)) {
		throw nd::exception(
				"Invalid call for, _m_ops::write_vec_vec_vec(...),\n\t"
						"LHS: coords::iter_type - require_linear_iterator(...)");
	}

	if (require_no_iterator(out_attr)
			&& (size0 != size1 || out_size != size0)) {

		throw nd::exception("_m_ops::write_vec_vec(...), size must be same,\n\t"
				"attr0.size1d == attr1.size1d,\n\t"
				"out_attr.iter_type - require_no_iterator(...)");
	}

	// ==================================================================

	// case: 0  (i.e. no broadcast)
	if (require_no_iterator(out_attr)) {

		// [0]
		nd::iterator::Iterator *iter0 = nd::iterator::init_iterator(attr0);
		nd::iterator::Iterator *iter1 = nd::iterator::init_iterator(attr1);

		big_size_t i = 0;

		do {

			T1 *v0 = d0 + iter0->index();
			T2 *v1 = d1 + iter1->index();

			func(res[i++], *v0, *v1);

		} while (iter0->next() && iter1->next());

		// [1]
		nd::iterator::free_iterator(iter0);
		nd::iterator::free_iterator(iter1);
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

	// [0]
	nd::iterator::Iterator *iter = nd::iterator::init_iterator(attr);

	big_size_t i = 0;

	do {

		res[i++] = func(d[iter->index()]);

	} while (iter->next());

	// [1]
	nd::iterator::free_iterator(iter);
}

/* [6] - lhs = rhs | res = sum(d0[i0:i1] * d1[j0:j1])
 *
 * 		ex. use-case -> nd::linalg::matmul(...)
 */
template<typename RT, typename T1, typename T2>
void mul_reduce_sum(RT *res, T1 *d0, T2 *d1, coords out_attr, coords attr0,
		coords attr1, max_size_t reduce_ndim) {

	nd::iterator::PairwiseSequential pseqIter(attr0, attr1);

	coords aligned_attr = pseqIter.aligned_coords(2);

	max_size_t aligned_ndim = aligned_attr.ndim;

	if (aligned_ndim < reduce_ndim) {

		throw nd::exception("...");
	}

	big_size_t n_chunk = aligned_attr.shape.multiply(0,
			aligned_ndim - reduce_ndim);

	big_size_t chunk_size = aligned_attr.shape.multiply(
			aligned_ndim - reduce_ndim, aligned_ndim);

	big_size_t aux_size = nd::mem::clip_dim(chunk_size);

	vec1d<RT> elems(aux_size, 0);

	big_size_t ij;
	big_size_t vi;

	for (big_size_t i = 0; i < n_chunk; i++) {

		ij = 0;
		vi = 0;

		elems.fill(aux_size, 0);

		do {

			elems[vi++] += (d0[pseqIter.index(0)] * d1[pseqIter.index(1)]);

			if (vi >= aux_size) {
				vi = 0;
			}

			ij++;

		} while (pseqIter.next() && (ij < chunk_size));

		res[i] = algorithm::sum<RT>(0, aux_size, elems.ref(0));
	}

}

}

#endif /* SRC_MULTIDIM_UFUNC_HPP */
