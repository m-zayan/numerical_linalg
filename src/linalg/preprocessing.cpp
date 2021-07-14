/*
 * preprocessing.cpp
 *
 *      Author: Z. Mohamed
 */

#include "linalg.hpp"

/*
 * mat.shape() ---> (reduced_dims, nrows, ncols)
 * column_index ---> pivot
 *
 * ### ccols:
 * 		for an augmented-matrix <--> [ccols < ncols]
 *
 * {1: valid-step, -1: invalid-step}
 *
 * 		 [invalid-step <--> singular-matrix-indicator]
 */
template<typename T, bool ref_h>
flag8_t nd::linalg::_h::partial_pivoting_step(nd::matrix<T, ref_h> &mat,
		nd::iterator::Iterator *it, max_size_t ccols, max_size_t column_index,
		bool pivot, bool scale) {

	max_size_t ndim = mat.ndim();

	max_size_t n_chunk = mat.shape()[0];
	max_size_t nrows = mat.shape()[1];
	max_size_t ncols = mat.shape()[2];

	if (ndim != 3) {
		throw nd::exception(
				"Invalid Call for, nd::linalg::_h::partial_pivoting_step(...)\n\t"
						"ndim != 3");
	}

	if (ncols <= column_index || nrows <= column_index) {
		throw nd::exception(
				"Invalid Call for, nd::linalg::_h::partial_pivoting_step(...)\n\t"
						"ncols <= column_index || nrows <= column_index");
	}

	if (std::is_integral<T>::value && scale) {
		throw nd::exception(
				"Invalid Call for, nd::linalg::_h::partial_pivoting_step(...)\n\t"
						"std::is_integral<T>::value && scale");
	}

	T *d = mat._m_begin();

	shape_t indices(ndim);

	T MAX = std::numeric_limits<T>::min();
	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();

	// epsilon
	T EPS = LINALG_EPS;
	T IEPS = LINALG_IEPS;

	for (max_size_t k = 0; k < n_chunk; k++) {

		// [0] ============================================================

		big_size_t index;

		indices[0] = k;

		// [1] ============================================================

		indices[1] = nrows - 1;
		indices[2] = ccols - 1;

		BITER_ROTATE_AT(it, indices);

		// [2] ============================================================

		if (pivot) {

			std::pair<T, max_size_t> mx = { MAX, invalid_idx };

			indices[2] = column_index;

			for (max_size_t i = column_index; i < nrows; i++) {

				indices[1] = i;

				BITER_INDEX_AT1D(it, indices, index);

				// largest absolute value
				if (mx.first < std::abs(d[index])) {
					mx = { std::abs(d[index]), i };
				}
			}

			// -------------------------------------------------------------

			max_size_t max_index = mx.second;

			// case: zero | invalid-step
			if (max_index == invalid_idx) {
				return -1;
			}

			else if (max_index != column_index) {

				big_size_t idx0, idx1;

				for (max_size_t i = 0; i < ncols; i++) {

					indices[1] = column_index;
					indices[2] = i;

					BITER_INDEX_AT1D(it, indices, idx0);

					indices[1] = max_index;
					indices[2] = i;

					BITER_INDEX_AT1D(it, indices, idx1);

					// permute row (column_index, max_index)
					std::swap(d[idx0], d[idx1]);
				}
			}
		}

		// [3] ============================================================

		if (scale) {

			indices[1] = column_index;
			indices[2] = column_index;

			BITER_INDEX_AT1D(it, indices, index);

			T scale_inv;

			if (d[index] == 0) {

				if (pivot) {

					// Debugging ... | must have been executed in case-zero
					throw nd::exception(
							"nd::linalg::_h::partial_pivoting_step(...), has been failed");
				}

				else {
					continue;
				}
			}

			// case: overflow
			else if (std::abs(d[index]) < EPS) {

				scale_inv = IEPS * algorithm::sign(d[index]);
			}

			else {

				scale_inv = 1.0 / d[index];
			}

			for (max_size_t i = 0; i < ncols; i++) {

				indices[1] = column_index;
				indices[2] = i;

				BITER_INDEX_AT1D(it, indices, index);

				// scale
				d[index] *= scale_inv;
			}
		}

	}

	// valid-step
	return 1;
}

/*
 * mat.shape() ---> (reduced_dims, nrows, ncols)
 *
 * ### ccols:
 * 		for an augmented-matrix <--> [ccols < ncols]
 *
 * {-1: invalid-step,
 *  0: last-pivot,
 *  1: first-pivot,
 *  2: valid-step}
 *
 * 		[invalid-step <--> singular-matrix-indicator]
 */

template<typename T, bool ref_h>
flag8_t nd::linalg::_h::gsubstitution_step(nd::matrix<T, ref_h> &mat,
		nd::iterator::Iterator *it, max_size_t ccols, max_size_t column_index,
		bool pivot) {

	flag8_t is_valid = nd::linalg::_h::partial_pivoting_step(mat, it, ccols,
			column_index, pivot, true);

	// case: invalid-step
	if (is_valid == -1) {
		return -1;
	}

	max_size_t ndim = mat.ndim();

	max_size_t n_chunk = mat.shape()[0];
	max_size_t nrows = mat.shape()[1];
	max_size_t ncols = mat.shape()[2];

	// case: last-pivot || first-pivot
	if (column_index + 1 == nrows) {
		return it->virtrot;
	}

	T *d = mat._m_begin();

	shape_t indices(ndim);

	big_size_t idx0, idx1;

	for (max_size_t k = 0; k < n_chunk; k++) {

		indices[0] = k;

		// [0] ============================================================

		indices[1] = nrows - 1;
		indices[2] = ccols - 1;

		BITER_ROTATE_AT(it, indices);

		// [1] ============================================================

		for (max_size_t i = column_index + 1; i < nrows; i++) {

			indices[1] = i;
			indices[2] = column_index;

			BITER_INDEX_AT1D(it, indices, idx1);

			T scale = d[idx1];

			for (max_size_t j = 0; j < ncols; j++) {

				indices[1] = column_index;
				indices[2] = j;

				BITER_INDEX_AT1D(it, indices, idx0);

				indices[1] = i;
				indices[2] = j;

				BITER_INDEX_AT1D(it, indices, idx1);

				// elimination step
				d[idx1] -= (d[idx0] * scale);
			}
		}
	}

	// case: valid-step
	return 1;
}
