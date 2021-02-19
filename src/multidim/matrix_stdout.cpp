/*
 * matrix_stdout.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

namespace nd::out::_h {

template<typename T>
void print_vec1d(T *data, RandomAccessNdIterator iter, big_size_t begin,
		big_size_t end) {

	std::cout << "[";

	for (big_size_t i = begin; i < end - 1; i++) {
		std::cout << data[iter.index_at(i)] << ", ";
	}

	std::cout << data[iter.index_at(end - 1)] << "]";

}

template<typename T>
void print_vec1d(T *data, big_size_t begin, big_size_t end) {

	std::cout << "[";

	for (big_size_t i = begin; i < end - 1; i++) {
		std::cout << data[i] << ", ";
	}

	std::cout << data[end - 1] << "]";

}

}

namespace nd::out {

template<typename T, bool ref_holder, flag8_t d_round = 0>
void print_matrix(matrix<T, ref_holder> mat) {

	RandomAccessNdIterator rndIter(mat._m_coords());

	T *data = mat._m_begin();

	max_size_t step = mat.step_size();
	max_size_t ndim = mat.ndim();
	big_size_t size = mat.size();

	shape_t strides = mat.strides();

	if (ndim > 1) {
		std::cout << "[";
	}

	for (big_size_t i = 0; i < size; i += step) {

		if (ndim > 1) {
			for (max_size_t j = 0; j < ndim - 2; j++) {

				if (i % strides[j] == 0) {
					for (max_size_t k = 0; k < ndim - j - 2; k++) {

						std::cout << "[";
					}

					break;
				}
			}
		}

		_h::print_vec1d(data, rndIter, i, i + step);

		if (ndim > 1) {
			for (max_size_t j = 0; j < ndim - 2; j++) {

				if ((i + step) % strides[j] == 0) {
					for (max_size_t k = 0; k < ndim - j - 2; k++) {

						std::cout << "]";
					}

					if (i == size - step) {
						std::cout << ']';
					} else {
						for (max_size_t k = 0; k < ndim - j - 2; k++) {

							std::cout << "\n";
						}
					}
					break;
				}
			}

			if ((i == size - step && ndim == 2)) {
				std::cout << "]";
			}
		}

		std::cout << '\n';
	}
}
}

