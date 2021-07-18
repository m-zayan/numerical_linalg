/*
 * experimental.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./linalg.hpp"

/*
 * # Brief Analysis for the 2D case,
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
 *	i.e. nd::deprecated::iterator::RandomAccess::reversed_index_at(...), and
 *		 nd::deprecated::iterator::RandomAccess::index_at(...), see also [2] section 3.
 */
template<typename T, bool rf_h>
void nd::v0::linalg::inplace::transpose(nd::matrix<T, rf_h> &mat, shape_t axes) {

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

	nd::deprecated::iterator::RandomAccess rndIter(new_attr);
	nd::deprecated::iterator::RandomAccess prev_rndIter(attr);

	strides_t reordered_strides = coords(new_attr.shape).strides;

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



