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

template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>* nd::_matrix<T, ref_holder>::_m_dynamic_cast() {

	return dynamic_cast<nd::matrix<T, ref_holder>*>(this);
}

template<typename T, bool ref_holder>
nd::_matrix<T, ref_holder>::~_matrix() {

}

// true
template<typename T>
nd::matrix<T, true>::matrix(shape_t shape) {

	this->attr = coords(shape);
	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size()));

	this->c_begin = 0;
	this->c_end = this->size();
}

template<typename T>
nd::matrix<T, true>::matrix(shape_t shape, T val) {

	this->attr = coords(shape);
	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size(), val));

	this->c_begin = 0;
	this->c_end = this->size();
}

template<typename T>
nd::matrix<T, true>::matrix(const coords &attr) {

	this->attr = std::move(attr);
	this->attr.own_data = true;

	this->c_begin = 0;
	this->c_end = this->size();

	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size()));

}

template<typename T>
nd::matrix<T> nd::matrix<T, true>::copy() {

	return this->reordered_chunk(false);
}

template<typename T>
nd::matrix<T, true>::~matrix() {

}

// false
template<typename T>
nd::matrix<T, false>::matrix(const coords &attr, shared_ptr<vec1d<T>> data,
		big_size_t c_begin, big_size_t c_end) {

	if (attr.own_data) {

		// debuging
		throw nd::exception("...");
	}

	this->attr = std::move(attr);

	this->data = data;

	this->c_begin = c_begin;
	this->c_end = c_end;
}

template<typename T>
nd::matrix<T, false>::matrix(const coords &attr, weak_ptr<vec1d<T>> data,
		big_size_t c_begin, big_size_t c_end) {

	if (attr.own_data) {

		// debuging
		throw nd::exception("...");
	}

	this->attr = std::move(attr);

	this->data = data;

	this->c_begin = c_begin;
	this->c_end = c_end;
}

template<typename T>
nd::matrix<T> nd::matrix<T, false>::copy() {

	return this->reordered_chunk(true);
}

template<typename T>
nd::matrix<T, false>::~matrix() {

}

// functions
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

	T *dr = result._m_begin();

	big_size_t slice = 0;

	for (max_size_t i = 0; i < matrix_list.size(); i++) {

		T *d = matrix_list[i]._m_begin();

		for (big_size_t j = 0; j < matrix_list[i].size(); j++) {

			dr[slice + j] = d[j];
		}

		slice += (i + 1) * matrix_list[i].size();
	}

	return result;
}

// #random
template<typename T>
nd::matrix<T> nd::random::uniform(T low, T high, shape_t shape) {

	nd::matrix<T> mat(shape);

	T *d = mat._m_begin();

	for (big_size_t i = 0; i < mat.size(); i++) {

		d[i] = generator<T>::random_uniform(low, high);
	}

	return mat;
}

// end functions
