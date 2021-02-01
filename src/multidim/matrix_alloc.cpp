/*
 * matrix_alloc.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

template<typename T>
nd::matrix<T>::matrix(shape_t shape) {

	this->attr = coords(shape);
	this->data.resize(this->attr.size1d);
}

/*
 * Initialize - C-order, n-dimension matrix using 1d - storage.
 *
 * Acess values, using nd_strides array.
 * stride - dictates the number of elements have to be skipped,
 * to get the next element in that dimension.
 */
template<typename T>
nd::matrix<T>::matrix(shape_t shape, T val) {

	this->attr = coords(shape);
	this->data.resize(this->attr.size1d);

	for (big_size_t i = 0; i < this->attr.size1d; i++) {

		this->data[i] = allocator::val_to_shared_ptr<T>(val);
	}
}

template<typename T>
nd::matrix<T>::matrix(const vec1d<ref_t<T>> &&chunk_data, const coords &&attr) :
		data(std::move(chunk_data)), attr(std::move(attr)) {
}

template<typename T>
nd::matrix<T>::matrix(const matrix &&mat) noexcept :
		data(std::move(mat.data)), attr(std::move(mat.attr)) {
}

template<typename T>
nd::matrix<T>::matrix(const matrix &mat) noexcept :
		data(mat.data), attr(mat.attr) {
}

template<typename T>
nd::matrix<T>::~matrix() {
}

template<typename T>
nd::matrix<T> nd::matrix<T>::copy() {

	nd::matrix<T> mat(this->shape());

	for (big_size_t i = 0; i < mat.size(); i++) {
		mat.data[i] = allocator::val_to_shared_ptr<T>(*this->data[i]);
	}

	return mat;
}

template<typename T>
nd::matrix<T> nd::stack(nd::composite<nd::matrix<T>> matrix_list) {

	if (matrix_list.size() == 0) {

		throw nd::exception(
				"nd::composite<nd::matrix<T>>:: matrix_list is empty");
	}

	for (max_size_t i = 0; i < matrix_list.size() - 1; i++) {

		if (matrix_list[i].shape() != matrix_list[i + 1].shape()
				|| matrix_list[i].ndim() != matrix_list[i + 1].ndim()) {

			throw nd::exception(
					"nd::matrix<T>::stack, matrices must have the same shape");
		}
	}

	max_size_t ndim = matrix_list[0].ndim();
	shape_t shape = matrix_list[0].shape();

	shape_t new_shape(ndim + 1);

	new_shape[0] = matrix_list.size();

	for (max_size_t i = 0; i < ndim; i++) {

		new_shape[i + 1] = shape[i];
	}

	nd::matrix<T> result(new_shape);

	big_size_t slice = 0;

	for (max_size_t i = 0; i < matrix_list.size(); i++) {

		for (big_size_t j = 0; j < matrix_list[i].size(); j++) {

			result.data[slice + j] = allocator::val_to_shared_ptr<T>(
					*matrix_list[i].data[j]);
		}

		slice += (i + 1) * matrix_list[i].size();
	}

	return result;
}

// ============ random ===========

template<typename T>
nd::matrix<T> nd::random::uniform(T low, T high, shape_t shape) {

	nd::matrix<T> mat(shape);

	for (big_size_t i = 0; i < mat.size(); i++) {

		T val = generator<T>::random_uniform(low, high);
		mat.data[i] = allocator::val_to_shared_ptr<T>(val);
	}

	return mat;
}
