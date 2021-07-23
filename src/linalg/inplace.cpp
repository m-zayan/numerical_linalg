/*
 * inplace.cpp
 *
 *      Author: Z. Mohamed
 */

#include "linalg.hpp"

/*
 * mat.shape() ---> (reduced_dims, nrows, ncols)
 * column_index ---> pivot
 *
 * ### ppcols:
 * 		e.g. for an augmented-matrix <--> [ppcols < ncols]
 *
 * {1: valid-step, -1: invalid-step}
 *
 * 		 [invalid-step <--> singular-matrix-indicator]
 */
template<typename T1, typename T2, bool rf_h0, bool rf_h1 = false>
flag8_t nd::linalg::inplace::partial_pivoting_step(nd::matrix<T1, rf_h0> &lhs,
		nd::iterator::Iterator *it, max_size_t ppcols, max_size_t column_index,
		bool pivot, bool scale, nd::matrix<T2, rf_h1> *rhsref) {

	max_size_t ndim = lhs.ndim();

	// -------------------------------------------------------------------------------

	if (ndim != 3) {
		throw nd::exception(
				"Invalid Call for, nd::linalg::inplace::partial_pivoting_step(...)\n\t"
						"ndim != 3");
	}

	// -------------------------------------------------------------------------------

	max_size_t n_chunk = lhs.shape()[0];
	max_size_t nrows = lhs.shape()[1];
	max_size_t ncols = lhs.shape()[2];

	// -------------------------------------------------------------------------------

	max_size_t rndim;
	max_size_t rn_chunk;
	max_size_t rnrows;
	max_size_t rncols;

	// -------------------------------------------------------------------------------

	if (ncols <= column_index || nrows <= column_index) {
		throw nd::exception(
				"Invalid Call for, nd::linalg::inplace::partial_pivoting_step(...)\n\t"
						"ncols <= column_index || nrows <= column_index");
	}

	if ((std::is_integral<T1>::value || std::is_integral<T2>::value) && scale) {
		throw nd::exception(
				"Invalid Call for, nd::linalg::inplace::partial_pivoting_step(...)\n\t"
						"std::is_integral<...>::value && scale");
	}

	// -------------------------------------------------------------------------------

	T1 *d = lhs._m_begin();

	T2 *b;

	// -------------------------------------------------------------------------------

	if (rhsref != nullptr) {

		rndim = rhsref->ndim();

		if (rndim != 3) {
			throw nd::exception(
					"Invalid Call for, nd::linalg::inplace::partial_pivoting_step(...)\n\t"
							"rndim != 3");
		}

		rn_chunk = rhsref->shape()[0];
		rnrows = rhsref->shape()[1];
		rncols = rhsref->shape()[2];

		if (rndim != ndim || rn_chunk != n_chunk || rnrows != nrows) {
			throw nd::exception(
					"Invalid Call for, nd::linalg::inplace::partial_pivoting_step(...)\n\t"
							"inconsistent [lhs | rhs]");
		}

		b = rhsref->_m_begin();
	}

	// -------------------------------------------------------------------------------

	shape_t rbegin(ndim);
	shape_t rend(ndim);

	shape_t indices(ndim);

	T1 MAX = std::numeric_limits<T1>::min();
	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();

	// epsilon
	T1 EPS = std::numeric_limits<T1>::epsilon();
	T1 IEPS = std::numeric_limits<T1>::max();

	big_size_t index;

	for (max_size_t k = 0; k < n_chunk; k++) {

		// [0] ============================================================

		rbegin[0] = rend[0] = indices[0] = k;

		// -------------------------------------------------------------

		rbegin[1] = rbegin[2] = 0;

		// -------------------------------------------------------------

		rend[1] = nrows - 1;
		rend[2] = ppcols - 1;

		// -------------------------------------------------------------

		BITER_ROTATE_AT(it, rbegin, rend);

		// [1] ============================================================

		if (pivot) {

			std::pair<T1, max_size_t> mx = { MAX, invalid_idx };

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

				// -------------------------------------------------------------

				if (rhsref != nullptr) {

					for (max_size_t i = 0; i < rncols; i++) {

						indices[1] = column_index;
						indices[2] = i;

						BITER_INDEX_AT1D(it, indices, idx0);

						indices[1] = max_index;
						indices[2] = i;

						BITER_INDEX_AT1D(it, indices, idx1);

						// permute row (column_index, max_index)
						std::swap(b[idx0], b[idx1]);
					}
				}
			}
		}

		// [2] ============================================================

		if (scale) {

			indices[1] = column_index;
			indices[2] = column_index;

			BITER_INDEX_AT1D(it, indices, index);

			T1 scale_inv;

			if (d[index] == 0) {

				if (pivot) {

					// Debugging ... | must have been executed in case-zero
					throw nd::exception(
							"nd::linalg::inplace::partial_pivoting_step(...), has been failed");
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

			// -------------------------------------------------------------

			for (max_size_t i = 0; i < ncols; i++) {

				indices[1] = column_index;
				indices[2] = i;

				BITER_INDEX_AT1D(it, indices, index);

				// scale
				d[index] *= scale_inv;
			}

			// -------------------------------------------------------------

			if (rhsref != nullptr) {

				for (max_size_t i = 0; i < rncols; i++) {

					indices[1] = column_index;
					indices[2] = i;

					BITER_INDEX_AT1D(it, indices, index);

					// scale
					b[index] *= scale_inv;
				}
			}
		}

	}

	// valid-step
	return 1;
}

/* ==================================================================================== */

/*
 * mat.shape() ---> (reduced_dims, nrows, ncols)
 *
 * ### gscols:
 * 		e.g. for an augmented-matrix <--> [gscols < ncols]
 *
 * {-1: invalid-step,
 *  0: last-pivot,
 *  1: first-pivot,
 *  2: valid-step}
 *
 * 		[invalid-step <--> singular-matrix-indicator]
 */

template<typename T1, typename T2, bool rf_h0, bool rf_h1 = false>
flag8_t nd::linalg::inplace::gsubstitution_step(nd::matrix<T1, rf_h0> &lhs,
		nd::iterator::Iterator *it, max_size_t gscols, max_size_t column_index,
		bool pivot, nd::matrix<T2, rf_h1> *rhsref) {

	flag8_t is_valid = nd::linalg::inplace::partial_pivoting_step(lhs, it,
			gscols, column_index, pivot, true, rhsref);

	// case: invalid-step
	if (is_valid == -1) {
		return -1;
	}

	// -------------------------------------------------------------------------------

	max_size_t ndim = lhs.ndim();

	max_size_t n_chunk = lhs.shape()[0];
	max_size_t nrows = lhs.shape()[1];
	max_size_t ncols = lhs.shape()[2];

	// -------------------------------------------------------------------------------

	max_size_t rndim;
	max_size_t rn_chunk;
	max_size_t rnrows;
	max_size_t rncols;

	// -------------------------------------------------------------------------------

	// case: last-pivot || first-pivot
	if (column_index + 1 == nrows) {
		return it->bit[1];
	}

	// -------------------------------------------------------------------------------

	T1 *d = lhs._m_begin();

	T2 *b;

	// -------------------------------------------------------------------------------

	if (rhsref != nullptr) {

		rndim = rhsref->ndim();

		rn_chunk = rhsref->shape()[0];
		rnrows = rhsref->shape()[1];
		rncols = rhsref->shape()[2];

		if (rndim != ndim || rn_chunk != n_chunk || rnrows != nrows) {

			// Debugging ... | must have been executed <--> partial_pivoting_step(...)
			throw nd::exception(
					"Invalid Call for, nd::linalg::inplace::gsubstitution_step(...)\n\t"
							"inconsistent [lhs | rhs]");
		}

		b = rhsref->_m_begin();
	}

	// -------------------------------------------------------------------------------

	shape_t rbegin(ndim);
	shape_t rend(ndim);

	shape_t indices(ndim);

	big_size_t idx0, idx1;

	for (max_size_t k = 0; k < n_chunk; k++) {

		rbegin[0] = rend[0] = indices[0] = k;

		// [0] ============================================================

		rbegin[1] = rbegin[2] = 0;

		rend[1] = nrows - 1;
		rend[2] = gscols - 1;

		BITER_ROTATE_AT(it, rbegin, rend);

		// [1] ============================================================

		for (max_size_t i = column_index + 1; i < nrows; i++) {

			indices[1] = i;
			indices[2] = column_index;

			BITER_INDEX_AT1D(it, indices, idx1);

			T1 scale = d[idx1];

			// -------------------------------------------------------------

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

			// -------------------------------------------------------------

			if (rhsref != nullptr) {

				for (max_size_t j = 0; j < rncols; j++) {

					indices[1] = column_index;
					indices[2] = j;

					BITER_INDEX_AT1D(it, indices, idx0);

					indices[1] = i;
					indices[2] = j;

					BITER_INDEX_AT1D(it, indices, idx1);

					// elimination step
					b[idx1] -= (b[idx0] * scale);
				}
			}
		}
	}

	// case: valid-step
	return 1;
}
