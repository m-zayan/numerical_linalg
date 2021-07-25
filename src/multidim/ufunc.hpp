/*
 * ufunc.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_MULTIDIM_UFUNC_HPP
#define SRC_MULTIDIM_UFUNC_HPP

//#include "../iterators/Pairwise.hpp"
//#include "../iterators/Sequential.hpp"

#include "../deprecated/iterators/RandomAccess.hpp"
#include "../iterators/factory.hpp"

#include "../wrappers/ops.hpp"

#include "../random/generator.hpp"

namespace _m_ops {

// [0] - lhs = rhs | d0 = func(d0, d1)
template<typename T1, typename T2>
void write_vec_vec(T1 *d0, T2 *d1, coords attr0, coords attr1,
		std::function<void(T1&, T1, T2)> func) {

	uflag8_t state = validate_op_bounds(attr0, attr1,
			"_m_ops::write_vec_vec(...), ");

	// (attr0 &  attr1) <--> scalar-like nd::matrix<T, ...>
	if (state == 0) {

		func(*d0, *d0, *d1);

		return;
	}

	// ==================================================================

	// [0]
	nd::iterator::Iterator *it0 = nd::iterator::init_iterator(attr0);
	nd::iterator::Iterator *it1 = nd::iterator::init_iterator(attr1);

	big_size_t niter = std::max(it0->niter, it1->niter);

	for (big_size_t i = 0; i < niter; i++) {

		T1 *v0 = d0 + it0->index1d;
		T2 *v1 = d1 + it1->index1d;

		func(*v0, *v0, *v1);

		ITER_PAIRWISE2_NEXT(it0, it1);
	}

	// [1]
	nd::iterator::free_iterator(it0);
	nd::iterator::free_iterator(it1);

}

// [1] - lhs = rhs | d = func(d, val)
template<typename T1, typename T2>
void write_val_vec(T1 *d, T2 val, coords attr,
		std::function<void(T1&, T1, T2)> func) {

	// scalar-like nd::matrix<T, ...>
	if (has_no_implicit_bounds(attr)) {

		func(*d, *d, val);

		return;
	}

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_iterator(attr);

	big_size_t niter = it->niter;

	for (big_size_t i = 0; i < niter; i++) {

		T1 *v = d + it->index1d;

		func(*v, *v, val);

		ITER_NEXT(it);

	}

	// [1]
	nd::iterator::free_iterator(it);
}

/* [2] - lhs = rhs | res = d | use-case -> type-casting
 *
 * broadcastable (i.e. repeat)
 */
template<typename RT, typename T>
void copy(RT *res, T *d, coords attr, coords out_attr) {

	uflag8_t state = validate_op_bounds(attr, out_attr, "_m_ops::copy(...), ");

	// (attr &  out_attr) <--> scalar-like nd::matrix<T, ...>
	if (state == 0) {

		res[0] = static_cast<RT>(d[0]);

		return;
	}

	// ==================================================================

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_iterator(attr);
	nd::iterator::Iterator *out_it = nd::iterator::init_iterator(out_attr);

	big_size_t niter = std::max(it->niter, out_it->niter);

	for (big_size_t i = 0; i < niter; i++) {

		res[out_it->index1d] = static_cast<RT>(d[it->index1d]);

		ITER_PAIRWISE2_NEXT(out_it, it);
	}

	// [1]
	nd::iterator::free_iterator(it);
	nd::iterator::free_iterator(out_it);

}

/* [3] - lhs = rhs | res = func(d, val) | ex. use-case -> boolean function
 *
 * broadcastable (i.e. repeat)
 */
template<typename RT, typename T1, typename T2>
void write_vec_val_vec(RT *res, T1 *d, T2 val, coords attr, coords out_attr,
		std::function<void(RT&, T1, T2)> func) {

	uflag8_t state = validate_op_bounds(attr, out_attr,
			"_m_ops::write_vec_val_vec(...), ");

	// (attr &  out_attr) <--> scalar-like nd::matrix<T, ...>
	if (state == 0) {

		func(*res, *d, val);

		return;
	}

	// ==================================================================

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_iterator(attr);
	nd::iterator::Iterator *out_it = nd::iterator::init_iterator(out_attr);

	big_size_t niter = std::max(it->niter, out_it->niter);

	for (big_size_t i = 0; i < niter; i++) {

		T1 *v = d + it->index1d;
		RT *r = res + out_it->index1d;

		func(*r, *v, val);

		ITER_PAIRWISE2_NEXT(out_it, it);
	}

	// [1]
	nd::iterator::free_iterator(it);
	nd::iterator::free_iterator(out_it);
}

/* [4] - lhs = rhs | res = func(d0, d1) | ex. use-case -> boolean function
 *
 * broadcastable
 */
template<typename RT, typename T1, typename T2>
void write_vec_vec_vec(RT *res, T1 *d0, T2 *d1, coords attr0, coords attr1,
		coords out_attr, std::function<void(RT&, T1, T2)> func) {

	uflag8_t state = validate_op_bounds(attr0, attr1,
			"_m_ops::write_vec_vec_vec(...), ", &out_attr);

	// (attr1 &  attr0 & out_attr) <--> scalar-like nd::matrix<T, ...>
	if (state == 0) {

		func(*res, *d0, *d1);

		return;
	}

	// ==================================================================

	// [0]
	nd::iterator::Iterator *it0 = nd::iterator::init_iterator(attr0);
	nd::iterator::Iterator *it1 = nd::iterator::init_iterator(attr1);
	nd::iterator::Iterator *out_it = nd::iterator::init_iterator(out_attr);

	big_size_t niter = out_it->niter;

	for (big_size_t i = 0; i < niter; i++) {

		T1 *v0 = d0 + it0->index1d;
		T2 *v1 = d1 + it1->index1d;

		RT *r = res + out_it->index1d;

		func(*r, *v0, *v1);

		ITER_PAIRWISE3_NEXT(out_it, it0, it1);
	}

	// [1]
	nd::iterator::free_iterator(it0);
	nd::iterator::free_iterator(it1);
	nd::iterator::free_iterator(out_it);
}

// [5] - lhs = rhs | res = func(d0)
/* [2] - lhs = rhs | res = d | use-case -> type-casting
 *
 * broadcastable (i.e. repeat)
 */
template<typename RT, typename T>
void write_vec(RT *res, T *d, coords attr, coords out_attr,
		std::function<RT(T)> func) {

	uflag8_t state = validate_op_bounds(attr, out_attr,
			"_m_ops::write_vec(...), ");

	// (attr &  out_attr) <--> scalar-like nd::matrix<T, ...>
	if (state == 0) {

		res[0] = func(d[0]);

		return;
	}

	// ==================================================================

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_iterator(attr);
	nd::iterator::Iterator *out_it = nd::iterator::init_iterator(out_attr);

	big_size_t niter = std::max(it->niter, out_it->niter);

	for (big_size_t i = 0; i < niter; i++) {

		res[out_it->index1d] = func(d[it->index1d]);

		ITER_PAIRWISE2_NEXT(out_it, it);
	}

	// [1]
	nd::iterator::free_iterator(it);
	nd::iterator::free_iterator(out_it);
}

/* [6] - lhs = rhs | res = sum(d0[i0:i1] * d1[j0:j1])
 *
 * 		ex. use-case -> nd::linalg::matmul(...)
 */
template<typename RT, typename T1, typename T2>
void mul_reduce_sum(RT *res, T1 *d0, T2 *d1, coords out_attr, coords attr0,
		coords attr1, max_size_t reduce_ndim) {

	coords aligned_attr = nd::align_dim(attr0, attr1);

	// [0]
	nd::iterator::Iterator *it0 = nd::iterator::init_iterator(attr0);
	nd::iterator::Iterator *it1 = nd::iterator::init_iterator(attr1);
	nd::iterator::Iterator *ait = nd::iterator::init_iterator(aligned_attr);

	max_size_t aligned_ndim = aligned_attr.ndim;

	if (aligned_ndim < reduce_ndim) {

		throw nd::exception(
				"_m_ops::mul_reduce_sum(...), aligned_ndim < reduce_ndim");
	}

	big_size_t n_chunk = aligned_attr.shape.multiply(0,
			aligned_ndim - reduce_ndim);

	big_size_t chunk_size = aligned_attr.shape.multiply(
			aligned_ndim - reduce_ndim, aligned_ndim);

	big_size_t aux_size = nd::mem::clip_dim(chunk_size);

	vec1d<RT> elems(aux_size, 0);

	RT *auxref = elems.ref(0);

	big_size_t vi;

	for (big_size_t k = 0; k < n_chunk; k++) {

		vi = 0;

		elems.fill(aux_size, 0);

		for (big_size_t i = 0; i < chunk_size; i++) {

			auxref[vi++] += (d0[it0->index1d] * d1[it1->index1d]);

			if (vi >= aux_size) {
				vi = 0;
			}

			ITER_PAIRWISE3_NEXT(ait, it0, it1);
		}

		res[k] = algorithm::sum<RT>(0, aux_size, auxref);
	}

	// [1]
	nd::iterator::free_iterator(it0);
	nd::iterator::free_iterator(it1);
	nd::iterator::free_iterator(ait);
}

// ==========================================================================================

template<typename T1, typename T2>
void contiguous_write_vec_val(T1 *d, T2 val, coords attr,
		std::function<void(T1&, T2)> func) {

	big_size_t size = attr.size1d;

	for (big_size_t i = 0; i < size; i++) {

		func(d[i], val);
	}

}

// ==========================================================================================

}

namespace _m_it {

template<typename RT, typename T>
void copy(RT *res, T *d, nd::iterator::Iterator *it,
		nd::iterator::Iterator *out_it) {

	big_size_t chunk_size = it->niter;

	for (big_size_t j = 0; j < chunk_size; j++) {

		res[out_it->index1d] = static_cast<RT>(d[it->index1d]);

		ITER_PAIRWISE2_NEXT(out_it, it);
	}
}

}

#endif /* SRC_MULTIDIM_UFUNC_HPP */
