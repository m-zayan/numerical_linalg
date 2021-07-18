/*
 * reshape.cpp
 *
 *      Author: Z. Mohamed
 */

#include "linalg.hpp"


/*
 *  nd::matrix<RT>::shape() <-->
 *
 *  		(reduced_dims, nrows, mat->ncols + aug->ncols)
 */
template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> nd::linalg::augmented(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1) {

	max_size_t ndim = m0.ndim();

	if (ndim < 2) {

		throw nd::exception("nd::linalg::augmented(...), ndim < 2");
	}

	if (m0.ndim() != m1.ndim()) {

		throw nd::exception(
				"nd::linalg::augmented, lhs & rhs must have the same ndim");
	}

	nd::matrix < T1, false > lhs = m0;
	nd::matrix < T2, false > rhs = m1;

	max_size_t axis = ndim - 2;

	vec1d < coords > in_attr = { m0._m_coords(), m1._m_coords() };
	coords out_attr = nd::concat_all(in_attr, axis);

	nd::matrix < RT > result(out_attr);

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_iterator(in_attr[0]);
	nd::iterator::Iterator *out_it = nd::iterator::init_iterator(out_attr);

	RT *res = result._m_begin();

	T1 *d0 = lhs._m_begin();
	T2 *d1 = rhs._m_begin();

	_m_it::copy<RT, T1>(res, d0, it, out_it);

	it->reinterpret_coords(in_attr[1]);

	_m_it::copy<RT, T2>(res, d1, it, out_it);

	// [1]
	nd::iterator::free_iterator(it);
	nd::iterator::free_iterator(out_it);

	return result.op_view_2d().permute( { 0, 2, 1 });
}

/*
 *  nd::matrix<RT>::shape() <-->
 *
 *  		(reduced_dims, nrows, mat->ncols + aug->ncols)
 *
 *  - [A | I]
 */
template<typename RT, typename T, bool rf_h>
nd::matrix<RT> nd::linalg::augmented(const nd::matrix<T, rf_h> &lhs) {

	// rhs <--> identity
	nd::matrix < RT > rhs = nd::linalg::eye < T > (lhs.shape());

	return nd::linalg::augmented < RT > (lhs, rhs);
}

