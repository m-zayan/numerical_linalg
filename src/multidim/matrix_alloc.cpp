/*
 * matrix_alloc.cpp
 *
 *	Author: Z. Mohamed
 *
 * Initialize - C-order, n-dimension matrix using vec1d - storage.
 *
 * Acess values, using strides array.
 * stride - dictates the number of elements have to be skipped,
 * to get the next element in that dimension.
 */

#include "./matrix.hpp"

template<typename T, bool shared_ref>
nd::matrix<T, shared_ref>::matrix(shape_t shape) {

	this->attr = coords(shape);
	this->data.resize(this->size());
}

template<typename T, bool shared_ref>
nd::matrix<T, shared_ref>::matrix(shape_t shape, T val) {

	this->attr = coords(shape);
	this->data.resize(this->attr.size1d);

	for (big_size_t i = 0; i < this->attr.size1d; i++) {

		this->data[i] = allocator::val_to_shared_ptr<T>(val);
	}
}
template<typename T, bool shared_ref>
nd::matrix<T, shared_ref>::matrix(const coords &&attr) {

	this->attr = std::move(attr);
	this->data.resize(this->attr.size1d);
}

template<typename T, bool shared_ref>
nd::matrix<T, shared_ref>::matrix(const matrix &&mat) noexcept :
		attr(std::move(mat._m_coords())), data(std::move(mat.data)) {
}

template<typename T, bool shared_ref>
nd::matrix<T, shared_ref>::matrix(const matrix &mat) noexcept :
		attr(mat._m_coords()), data(mat.data) {
}

template<typename T, bool shared_ref>
nd::matrix<T, shared_ref>::~matrix() {

}

template<typename T, bool shared_ref>
nd::matrix<T> nd::matrix<T, shared_ref>::copy() {

	nd::matrix<T> result(this->shape());

	for (big_size_t i = 0; i < this->size(); i++) {

		result.data[i] = allocator::val_to_shared_ptr(*this->data[i].get());
	}

	return result;
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
					*matrix_list[i].data[j].get());
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
