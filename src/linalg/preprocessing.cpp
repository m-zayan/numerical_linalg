/*
 * preprocessing.cpp
 *
 *      Author: Z. Mohamed
 */

#include "linalg.hpp"

template<typename T, bool ref_h>
void nd::linalg::_h::partial_pivoting(nd::matrix<T, ref_h> &mat,
		shape_t chunk_indices, max_size_t column_index) {

	max_size_t ndim = mat.ndim();

	max_size_t n_chunk = chunk_indices.size();

	if (ndim - n_chunk != 2) {
		throw nd::exception(
				"Invalid Call for, nd::linalg::_h::partial_pivoting(...)\n\t"
						"ndim - n_chunk != 2");
	}

	nd::matrix<T, false> temp = mat;

	coords attr = temp._m_coords();

	nd::iterator::RandomAccess rndIter(attr);

	max_size_t nrows = mat.shape()[ndim - 2];
	max_size_t ncols = mat.shape()[ndim - 1];

	T *d = temp._m_begin();

	// [0] ============================================================

	shape_t indices(ndim);

	for (max_size_t i = 0; i < n_chunk; i++) {
		indices[i] = chunk_indices[i];
	}

	indices[ndim - 1] = column_index;

	T MAX = std::numeric_limits<T>::min();
	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();

	std::pair<T, max_size_t> mx = { MAX, invalid_idx };

	big_size_t index;

	for (max_size_t i = 0; i < nrows; i++) {

		indices[ndim - 2] = i;

		index = rndIter.index_at(indices);

		// largest absolute value
		mx = std::max(mx, { std::abs(d[index]), i });
	}

	// [1] ============================================================

	max_size_t max_index = mx.second;

	big_size_t idx0, idx1;

	for (max_size_t i = 0; i < ncols; i++) {

		indices[ndim - 2] = column_index;
		indices[ndim - 1] = i;

		idx0 = rndIter.index_at(indices);

		indices[ndim - 2] = max_index;
		indices[ndim - 1] = i;

		idx1 = rndIter.index_at(indices);

		std::swap(d[idx0], d[idx1]);
	}

}

