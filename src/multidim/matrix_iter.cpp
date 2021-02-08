/*
 * matrix_iter.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

template<typename T, bool shared_ref>
nd::matrix<T, false> nd::matrix<T, shared_ref>::chunk_at(const coords &attr,
		big_size_t begin, big_size_t end) {

	nd::matrix<T, false> mat_chunk(std::move(attr));

	for (big_size_t i = begin; i < end; i++) {
		mat_chunk.data[i - begin] = this->data[i];
	}

	return mat_chunk;
}

template<typename T, bool shared_ref>
big_size_t nd::matrix<T, shared_ref>::index_at(shape_t indices) {

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
