/*
 * matrix_stdout.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

template<typename T>
void nd::matrix<T>::print_matrix() {

	max_size_t step = this->step_size();

	if (this->ndim() > 1) {
		std::cout << "[";
	}

	for (big_size_t i = 0; i < this->size(); i += step) {

		if (this->ndim() > 1) {
			for (max_size_t j = 0; j < this->ndim() - 2; j++) {

				if (i % this->strides()[j] == 0) {
					for (max_size_t k = 0; k < this->ndim() - j - 2; k++) {

						std::cout << "[";
					}

					break;
				}
			}
		}

		this->data.rprint_vec1d(i, i + step);

		if (this->ndim() > 1) {
			for (max_size_t j = 0; j < this->ndim() - 2; j++) {

				if ((i + step) % this->strides()[j] == 0) {
					for (max_size_t k = 0; k < this->ndim() - j - 2; k++) {

						std::cout << "]";
					}

					if (i == this->size() - step) {
						std::cout << ']';
					} else {
						for (max_size_t k = 0; k < this->ndim() - j - 2; k++) {

							std::cout << "\n";
						}
					}
					break;
				}
			}

			if ((i == this->size() - step && this->ndim() == 2)) {
				std::cout << "]";
			}
		}

		std::cout << '\n';
	}
}
