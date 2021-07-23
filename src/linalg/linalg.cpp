/*
 * linalg.cpp
 *
 *	Author: Z. Mohamed
 */

//#include "./linalg.hpp"
#include "./reshape.cpp"
#include "./inplace.cpp"

#include "./experimental.cpp"

template<typename RT>
nd::matrix<RT> nd::linalg::eye(shape_t shape, max_t dshift) {

	if (shape.size() == 0) {

		nd::exception("nd::linalg::eye(...), "
				"shape has to be greater than or equal 1, shape.size() == 0");
	}

	// -------------------------------------------------------------------------------

	nd::matrix<RT> result(shape, 0);

	// -------------------------------------------------------------------------------

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_2d_iterator(
			result._m_coords());

	// -------------------------------------------------------------------------------

	DI3_MOVE_ALONG(it, dshift);

	max_size_t chunk_size = DI3_NITER2(it);
	max_size_t n_chunk = DI3_NITER3(it);

	big_size_t niter = chunk_size * n_chunk;

	// -------------------------------------------------------------------------------

	RT *res = result._m_begin();

	// -------------------------------------------------------------------------------

	for (big_size_t i = 0; i < niter; i++) {

		res[it->index1d] = 1;

		DI3_NEXT(it);
	}

	// -------------------------------------------------------------------------------

	// [1]
	nd::iterator::free_iterator(it);

	return result;
}

/* ===================================================================================== */

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> nd::linalg::diag(const nd::matrix<T, rf_h> &mat, max_t dshift) {

	nd::matrix<T, false> tmp = mat;

	// -------------------------------------------------------------------------------

	coords mcoords = tmp._m_coords();
	coords view3d = mcoords.reinterpret_view3d(false);

	// -------------------------------------------------------------------------------

	max_size_t in_ndim = mcoords.ndim;
	max_size_t v_ndim = view3d.ndim;

	// -------------------------------------------------------------------------------

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_iterator(view3d);

	// -------------------------------------------------------------------------------

	DI3_MOVE_ALONG(it, dshift);

	max_size_t chunk_size = DI3_NITER2(it);
	max_size_t n_chunk = DI3_NITER3(it);

	// -------------------------------------------------------------------------------

	if (chunk_size == 0) {

		throw nd::exception("nd::linalg::diag(...),\n\t"
				"yields an empty nd::matrix<RT, ...>");
	}

	// -------------------------------------------------------------------------------

	shape_t out_shape;

	if (in_ndim > v_ndim) {

		out_shape = mcoords.shape.slice(0, in_ndim - 2);
	}

	else {

		out_shape = { n_chunk };
	}

	out_shape.emplace_back(chunk_size);

	// -------------------------------------------------------------------------------

	nd::matrix<RT> result(out_shape, 0);

	// -------------------------------------------------------------------------------

	// niter == result.size()
	big_size_t niter = chunk_size * n_chunk;

	// -------------------------------------------------------------------------------

	T *d = tmp._m_begin();

	RT *res = result._m_begin();

	// -------------------------------------------------------------------------------

	for (big_size_t i = 0; i < niter; i++) {

		res[i] = static_cast<RT>(d[it->index1d]);

		DI3_NEXT(it);
	}

	// -------------------------------------------------------------------------------

	// [1]
	nd::iterator::free_iterator(it);

	return result;
}

/* ===================================================================================== */

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> nd::linalg::matmul(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1) {

	coords attr0 = m0._m_coords();
	coords attr1 = m1._m_coords();

	// -------------------------------------------------------------------------------

	coords out_attr = nd::align_dim_2d(attr0, attr1,
			"nd::linalg::matmul(...), ");

	// -------------------------------------------------------------------------------

	attr0.ownership(false);
	attr1.ownership(false);

	// -------------------------------------------------------------------------------

	nd::matrix<T1, false> tmp0 = m0.set_new_coords(attr0);
	nd::matrix<T2, false> tmp1 = m1.set_new_coords(attr1);

	// -------------------------------------------------------------------------------

	nd::matrix<RT> result(out_attr);

	// -------------------------------------------------------------------------------

	T1 *d0 = tmp0._m_begin();
	T2 *d1 = tmp1._m_begin();

	RT *res = result._m_begin();

	// -------------------------------------------------------------------------------

	_m_ops::mul_reduce_sum(res, d0, d1, out_attr, tmp0._m_coords(),
			tmp1._m_coords(), 1);

	// -------------------------------------------------------------------------------

	result._m_clear_iter_type();

	return result;
}

/* ===================================================================================== */

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> nd::linalg::tensordot(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1, vec1d<shape_t> axes) {

	coords attr0 = m0._m_coords();
	coords attr1 = m1._m_coords();

	coords out_attr = nd::align_dim(attr0, attr1, axes,
			"nd::linalg::tensordot(...), ");

	// -------------------------------------------------------------------------------

	attr0.ownership(false);
	attr1.ownership(false);

	// -------------------------------------------------------------------------------

	nd::matrix<T1, false> tmp0 = m0.set_new_coords(attr0);
	nd::matrix<T2, false> tmp1 = m1.set_new_coords(attr1);

	// -------------------------------------------------------------------------------

	nd::matrix<RT> result(out_attr);

	// -------------------------------------------------------------------------------

	T1 *d0 = tmp0._m_begin();
	T2 *d1 = tmp1._m_begin();

	RT *res = result._m_begin();

	// -------------------------------------------------------------------------------

	// axes[0].size() == axes[1].size()
	max_size_t naxes = axes[0].size();

	_m_ops::mul_reduce_sum(res, d0, d1, out_attr, tmp0._m_coords(),
			tmp1._m_coords(), naxes);

	// -------------------------------------------------------------------------------

	result._m_clear_iter_type();

	return result;
}

/* ===================================================================================== */

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> nd::linalg::inner(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1) {

	max_size_t ndim0 = m0._m_coords().ndim;
	max_size_t ndim1 = m1._m_coords().ndim;

	// -------------------------------------------------------------------------------

	// multiply
	if (ndim0 == 0 || ndim1 == 0) {

		nd::matrix<T1, false> tmp0 = m0;
		nd::matrix<T2, false> tmp1 = m1;

		return (tmp0 * tmp1);

	}

	// vector inner product
	else if (ndim0 == 1 && ndim1 == 1) {

		nd::matrix<T1, false> tmp0 = m0;
		nd::matrix<T2, false> tmp1 = m1;

		return nd::numeric::sum<RT>((tmp0 * tmp1), 0, false);
	}

	else {

		return nd::linalg::tensordot<RT>(m0, m1,
				{ { ndim0 - 1 }, { ndim1 - 1 } });
	}
}

/* ===================================================================================== */

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> nd::linalg::dot(const nd::matrix<T1, rf_h0> &m0,
		const nd::matrix<T2, rf_h1> &m1) {

	max_size_t ndim0 = m0._m_coords().ndim;
	max_size_t ndim1 = m1._m_coords().ndim;

	// -------------------------------------------------------------------------------

	// multiply
	if (ndim0 == 0 || ndim1 == 0) {

		return nd::linalg::inner<RT>(m0, m1);
	}

	// vector inner product
	else if (ndim0 == 1 && ndim1 == 1) {

		return nd::linalg::inner<RT>(m0, m1);
	}

	else if (ndim0 == 2 && ndim1 == 2) {

		return nd::linalg::matmul<RT>(m0, m1);
	}

	else {

		return nd::linalg::tensordot<RT>(m0, m1,
				{ { ndim0 - 1 }, { ndim1 - 2 } });
	}
}

/* ===================================================================================== */

template<typename T, bool rf_h>
nd::matrix<T> nd::linalg::transpose(const nd::matrix<T, rf_h> &mat,
		shape_t axes) {

	return mat.permute(axes).copy();
}

/* ===================================================================================== */

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> nd::linalg::inverse(const nd::matrix<T, rf_h> &mat, bool pivot) {

	coords mcoords = mat._m_coords();
	coords cview3d = mcoords.reinterpret_view3d(false);

	// -------------------------------------------------------------------------------

	if (!mcoords.is_square()) {
		throw nd::exception("nd::linalg::inverse(...),\n\t"
				"nd::matrix<T, ...> - must be a square matrix");
	}

	// -------------------------------------------------------------------------------

	nd::matrix<RT> mcopy = mat.set_new_coords(cview3d);

	// -------------------------------------------------------------------------------

	nd::matrix<RT> result = nd::linalg::eye<RT>(mcoords.shape, 0);

	nd::matrix<RT, false> rview = result.set_new_coords(cview3d);

	// -------------------------------------------------------------------------------

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_iterator(cview3d);

	// -------------------------------------------------------------------------------

	flag8_t state;

	max_size_t ncols = cview3d.ncols();

	// -------------------------------------------------------------------------------

	// forward
	for (max_size_t i = 0; i < ncols; i++) {

		state = nd::linalg::inplace::gsubstitution_step(mcopy, it, ncols, i,
				pivot, &rview);

		if (state == -1) {
			throw nd::exception("nd::linalg::inverse(...),\n\t"
					"nd::matrix<T, ...> - singular matrix");
		}
	}

	// -------------------------------------------------------------------------------

	// backward
	BITER_ROTATE(it);

	for (max_size_t i = 0; i < ncols; i++) {

		state = nd::linalg::inplace::gsubstitution_step(mcopy, it, ncols, i,
				false, &rview);

		if (state == -1) {
			throw nd::exception("nd::linalg::inverse(...),\n\t"
					"nd::matrix<T, ...> - singular matrix");
		}
	}

	// -------------------------------------------------------------------------------

	// [1]
	nd::iterator::free_iterator(it);

	return result;
}
