/*
 * linalg.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./linalg.hpp"

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

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> nd::linalg::matmul(const nd::matrix<T1, rf_h0> &m1,
		const nd::matrix<T2, rf_h1> &m2) {

	nd::matrix<T1, true> mat1 = m1;
	nd::matrix<T2, true> mat2 = m2;

	max_size_t ndim_1 = mat1.ndim();
	max_size_t ndim_2 = mat2.ndim();

	if (!(ndim_1 >= 2 && ndim_2 >= 2)) {

		throw nd::exception(
				"Input dimension has to be greater than or equal 2, ndim >= 2");
	}

	max_size_t dim01 = mat1.shape()[ndim_1 - 1];
	max_size_t dim11 = mat1.shape()[ndim_1 - 2];

	max_size_t dim02 = mat2.shape()[ndim_2 - 1];
	max_size_t dim12 = mat2.shape()[ndim_2 - 2];

	if (dim01 != dim12) {

		throw nd::exception("Input: mismatch dimension 0");
	}

	shape_t new_shape;

	big_size_t n_chunk = 0;

	big_size_t chunk_size_1 = 0;
	big_size_t chunk_size_2 = 0;

	if (ndim_1 == ndim_2) { // else max(ndim_1, ndim_2)

		for (max_size_t i = 0; i < ndim_1 - 2; i++) {
			if (mat1.shape()[i] != mat2.shape()[i]) {
				throw nd::exception("Inputs: could not be broadcast, "
						"shapes are not aligned for: ndim > 2, ");
			}
		}

		new_shape = mat1.shape();
		new_shape[ndim_1 - 1] = dim02;

		n_chunk = mat1.shape().multiply(0, ndim_1 - 2);

		if (ndim_1 >= 3) {

			chunk_size_1 = mat1.strides()[ndim_1 - 3];
			chunk_size_2 = mat2.strides()[ndim_2 - 3];
		}
	}

	if (ndim_1 > ndim_2) {

		for (max_size_t i = 0; i < ndim_2 - 2; i++) {
			if (mat1.shape()[i] != mat2.shape()[i]) {
				throw nd::exception("mat1: Inputs: could not be broadcast, "
						"shapes are not aligned for: ndim > 2, ");
			}
		}

		new_shape = mat1.shape();
		new_shape[ndim_1 - 1] = dim02;

		n_chunk = mat1.shape().multiply(0, ndim_1 - 2);

		chunk_size_1 = mat1.strides()[ndim_1 - 3];

		if (ndim_2 >= 3) {

			chunk_size_2 = mat2.strides()[ndim_2 - 3];
		}

		else {
			chunk_size_2 = 0;
		}
	}

	if (ndim_1 < ndim_2) {

		for (max_size_t i = 0; i < ndim_1 - 2; i++) {
			if (mat1.shape()[i] != mat2.shape()[i]) {
				throw nd::exception("mat2: Inputs: could not be broadcast, "
						"shapes are not aligned for: ndim > 2, ");
			}
		}

		new_shape = mat2.shape();
		new_shape[ndim_1 - 1] = dim02;

		n_chunk = mat2.shape().multiply(0, ndim_2 - 2);

		if (ndim_1 >= 3) {

			chunk_size_1 = mat1.strides()[ndim_1 - 3];
		} else {
			chunk_size_1 = 0;
		}

		chunk_size_2 = mat2.strides()[ndim_2 - 3];

	}

	nd::matrix<RT> result(new_shape);

	T1 *d0 = mat1._m_begin();
	T2 *d1 = mat2._m_begin();
	RT *d2 = result._m_begin();

	max_size_t aux_size = std::min(dim12, nd::AUX_SIZE_2048);

	max_size_t vi;

	vec1d<RT> elems(aux_size, 0);

	big_size_t index = 0;

	for (big_size_t t = 0; t < n_chunk; t++) {

		big_size_t s1 = t * chunk_size_1;
		big_size_t s2 = t * chunk_size_2;

		for (big_size_t d11 = 0; d11 < dim11; d11++) {

			for (big_size_t d02 = 0; d02 < dim02; d02++) {

				elems.fill(aux_size, 0);
				vi = 0;

				for (big_size_t d12 = 0; d12 < dim12; d12++) {

					big_size_t l1 = s1 + (d12 + d11 * dim01);
					big_size_t l2 = s2 + (d02 + d12 * dim02);

					vi %= aux_size;

					elems[vi++] += (d0[l1] * d1[l2]);

				}

				d2[index++] = elems.sum(0, aux_size);
			}
		}

	}

	return result;
}

template<typename RT, typename T1, typename T2, bool rf_h0, bool rf_h1>
nd::matrix<RT> nd::linalg::dot(const nd::matrix<T1, rf_h0> &m1,
		const nd::matrix<T2, rf_h1> &m2) {

	nd::matrix<T1, true> mat1 = m1;
	nd::matrix<T2, true> mat2 = m2;

	max_size_t ndim_1 = mat1.ndim();
	max_size_t ndim_2 = mat2.ndim();

	if (!(ndim_1 >= 2 && ndim_2 >= 2)) {

		throw nd::exception(
				"Input dimension has to be greater than or equal 2, ndim >= 2");
	}

	if (ndim_1 == 2 || ndim_2 == 2) {

		throw nd::exception(
				"Input dimension < 2, consider using nd::matrix<T>::matmul instead");
	}

	max_size_t dim01 = mat1.shape()[ndim_1 - 1];

	max_size_t dim02 = mat2.shape()[ndim_2 - 1];
	max_size_t dim12 = mat2.shape()[ndim_2 - 2];

	if (dim01 != dim12) {

		throw nd::exception("Input: mismatch dimension 0");
	}

	shape_t shape_1 = mat1.shape();
	shape_t shape_2 = mat2.shape();

	max_size_t new_ndim = ndim_1 + ndim_2 - 2;
	shape_t new_shape(new_ndim);

	for (max_size_t i = 0; i < ndim_1 - 1; i++) {

		new_shape[i] = shape_1[i];
	}

	for (max_size_t i = 0; i < ndim_2 - 2; i++) {

		new_shape[ndim_1 + i - 1] = shape_2[i];
	}

	new_shape[new_ndim - 1] = shape_2[ndim_2 - 1];

	// mat2
	max_size_t step_02 = mat2.strides()[ndim_2 - 2];
	max_size_t step_12 = mat2.strides()[ndim_2 - 1];

	big_size_t steps_2 = 1;
	big_size_t chunk_size_2 = 1;

	big_size_t ik = 0;
	big_size_t slice_2 = 0;

	if (ndim_2 > 2) {

		steps_2 = mat2.size() / mat2.strides()[ndim_2 - 3];
		chunk_size_2 = (dim02 * dim12);
	}

	nd::matrix<RT> result(new_shape);

	// ...
	max_size_t step_size_1 = mat1.step_size();

	big_size_t steps_1 = mat1.size() / step_size_1;

	max_size_t aux_size = std::min(dim12, nd::AUX_SIZE_2048);

	vec1d<RT> elems(aux_size, 0);

	max_size_t vi;

	big_size_t index = 0;

	T1 *d0 = mat1._m_begin();
	T2 *d1 = mat2._m_begin();
	RT *d2 = result._m_begin();

	for (big_size_t i = 0; i < steps_1; i++) {

		big_size_t start = i * step_size_1;

		for (big_size_t k = 0; k < steps_2; k++) {

			slice_2 = k * chunk_size_2;

			for (max_size_t j = 0; j < dim02; j++) {

				elems.fill(aux_size, 0);
				vi = 0;

				for (max_size_t k = 0; k < dim12; k++) {

					ik = slice_2 + j * step_12 + k * step_02;

					vi %= aux_size;

					elems[vi++] += (d0[start + k] * d1[ik]);
				}

				d2[index++] = elems.sum(0, aux_size);
			}
		}
	}

	return result;
}

template<typename T, bool rf_h>
nd::matrix<T> nd::linalg::transpose(nd::matrix<T, rf_h> mat, shape_t axes) {

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
 *	i.e. RandomAccessNdIterator::reversed_index_at(...), and
 *		 RandomAccessNdIterator::index_at(...), see also [2] section 3.
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

	RandomAccessNdIterator rndIter(new_attr);

	for (big_size_t i = 0; i < size; i++) {

		T tmp = d[i];

		k = i;
		j = rndIter.index_at(i);
		xi = size;

		// no change
		if (i == j) {
			continue;
		}

		if (rndIter.is_cycle_root(i)) {

			while (true) {

				xi = rndIter.reversed_index_at(k);

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
