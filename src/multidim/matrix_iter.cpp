/*
 * matrix_iter.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

template<typename T>
void nd::matrix<T>::chunk_at(vec1d<std::shared_ptr<T>> &chunk_data,
		big_size_t begin, big_size_t end) {

	for (big_size_t i = begin; i < end; i++) {
		chunk_data[i - begin] = this->data[i];
	}
}

template<typename T>
big_size_t nd::matrix<T>::index_at(shape_t indices) {

	if (indices.size() != this->ndim()) {
		throw nd::exception("Dimensions Indices, Out of Range");
	}

	big_size_t index = 0;

	for (max_size_t i = 0; i < indices.size(); i++) {

		max_size_t step = this->strides()[i];

		index += (step * indices[i]);
	}

	return index;
}
