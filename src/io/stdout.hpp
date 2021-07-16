/*
 * stdout.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_IO_STDOUT_HPP
#define SRC_IO_STDOUT_HPP

#include "../multidim/matrix.hpp"

namespace nd::out::_h {

inline void print_rchar(char chr, max_size_t n) {

	for (max_size_t i = 0; i < n; i++) {
		std::cout << chr;
	}
}

template<typename T>
void it_print_vec1d(T *ref, nd::iterator::Iterator *it, big_size_t size) {

	for (big_size_t i = 0; i < size - 1; i++) {

		std::cout << ref[it->index1d] << ", ";

		ITER_NEXT(it);
	}

	std::cout << ref[it->index1d];

	ITER_NEXT(it);
}

template<typename T>
void print_vec1d(T *ref, big_size_t begin, big_size_t end) {

	std::cout << '[';

	for (big_size_t i = begin; i < end - 1; i++) {

		std::cout << ref[i] << ", ";
	}

	std::cout << ref[end - 1] << "]\n";
}

}

namespace nd::out {

template<typename T, bool rf_h>
void print_matrix(const matrix<T, rf_h> &mat) {

	nd::matrix<T, false> tmp = mat;

	coords mcoords = tmp._m_coords();

	T *data = tmp._m_begin();

	if (is_scalar(mcoords)) {
		std::cout << data[0] << '\n';
		return;
	}

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_iterator(mcoords);

	it->reinterpret_linear();

	big_size_t chunk_size = mat.step_size();
	big_size_t n_chunk = it->niter / chunk_size;

	nd::out::_h::print_rchar('[', it->ndim);

	for (big_size_t i = 0; i < n_chunk; i++) {

		nd::out::_h::print_rchar('[', it->ndim - it->iaxis - 1);

		nd::out::_h::it_print_vec1d<T>(data, it, chunk_size);

		nd::out::_h::print_rchar(']', it->ndim - it->iaxis - 1);

		if (i != n_chunk - 1) {
			nd::out::_h::print_rchar('\n', it->ndim - it->iaxis - 1);
		}
	}

	nd::out::_h::print_rchar(']', 1);
	nd::out::_h::print_rchar('\n', 1);

	// [1]
	nd::iterator::free_iterator(it);
}
}

#endif /* SRC_IO_STDOUT_HPP */
