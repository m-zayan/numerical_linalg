/*
 * linalg.cpp
 *
 *	Author: Z. Mohamed
 */

//#include "./linalg.hpp"
#include "./preprocessing.cpp"

template<typename T>
nd::matrix<T> nd::linalg::eye(shape_t shape) {

	if (shape.size() < 2) {

		nd::exception(
				"shape, has to be greater than or equal 2, shape.size() >= 2");
	}

	nd::matrix<T> mat(shape, 0);

	max_size_t ndim = mat.ndim();

	max_size_t step0 = shape[ndim - 1];
	max_size_t step1 = shape[ndim - 2];

	max_size_t step = std::min(step0, step1);

	big_size_t chunk_step = step0 * step1;

	big_size_t size = mat.size();

	big_size_t k;

	T *d = mat._m_begin();

	for (big_size_t i = 0; i < size; i += chunk_step) {

		k = 0;

		for (max_size_t j = 0; j < step; j++) {

			d[i + j + k] = 1;

			k += step0;
		}

	}

	return mat;
}

//template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
//nd::matrix<RT> nd::linalg::matmul(const nd::matrix<T1, rf_h0> &m0,
//		const nd::matrix<T2, rf_h1> &m1) {
//
//	coords attr0 = m0._m_coords();
//	coords attr1 = m1._m_coords();
//
//	attr0.own_data = false;
//	attr1.own_data = false;
//
//	coords out_attr = nd::align_dim_2d(attr0, attr1,
//			"nd::linalg::matmul(...), ");
//
//	nd::matrix<T1, true> mat0 = m0.set_new_coords(attr0);
//	nd::matrix<T2, true> mat1 = m1.set_new_coords(attr1);
//
//}

//template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
//nd::matrix<RT> nd::linalg::dot(const nd::matrix<T1, rf_h0> &m1,
//		const nd::matrix<T2, rf_h1> &m2) {
//
//
//}

template<typename T, bool rf_h>
nd::matrix<T> nd::linalg::transpose(const nd::matrix<T, rf_h> &mat,
		shape_t axes) {

	return mat.permute(axes).copy();
}

//inplace ops

/*
 * # 2D case,
 *
 * # shape = (N, M)
 * # n = N * M
 *
 * [1]
 *  space-complexity: O(1)
 *  time-complexity: O(n^2)
 *
 * # might be extended later, to a partially-in-place-transpose
 *
 * [2] https://link.springer.com/content/pdf/10.1007%2F978-3-540-75755-9_68.pdf,
 *
 * 	space-complexity: O((N + M)/2) of a bit type (ex. std::bitset)
 * 	time-complexity: O(n * log(n))
 *
 * [3] https://ctnzr.io/papers/PPoPP-2014.pdf,
 *
 *	space-complexity: O(max(N, M))
 *	time-complexity: O(n)
 *
 *	---
 *
 *	A possible optimization for [1], is to use BABE (Burn At Both Ends)
 *
 *	i.e. nd::iterator::RandomAccess::reversed_index_at(...), and
 *		 nd::iterator::RandomAccess::index_at(...), see also [2] section 3.
 */
template<typename T, bool rf_h>
void nd::linalg::inplace::transpose(nd::matrix<T, rf_h> &mat, shape_t axes) {

	// might be optional later
	if (!mat.own_data()) {
		throw nd::exception("nd::matrix, mat.own_data() == false");
	}

	big_size_t size = mat.size();
	shape_t shape = mat.shape();

	T *d = mat._m_begin();
	big_size_t j, k, xi;

	coords attr = mat._m_coords();
	coords new_attr = attr.permuted(axes, true);

	nd::iterator::RandomAccess rndIter(new_attr);
	nd::iterator::RandomAccess prev_rndIter(attr);

	shape_t reordered_strides = coords(new_attr.shape).strides;

	bool is_root;

	for (big_size_t i = 0; i < size; i++) {

		T tmp = d[i];

		k = i;
		j = rndIter.index_at(i);
		xi = size;

		// no change
		if (i == j) {
			continue;
		}

		is_root = rndIter.is_cycle_root(i, attr, prev_rndIter,
				reordered_strides);

		if (is_root) {

			while (true) {

				xi = rndIter.reversed_index_at(k, attr, prev_rndIter,
						reordered_strides);

				if (xi == i) {
					break;
				}

				std::swap(d[xi], tmp);
				k = xi;
			}

			// xi = i
			d[i] = tmp;
		}
	}

	mat._m_reshape(new_attr.shape);
}
