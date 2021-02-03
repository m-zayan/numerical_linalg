/*
 * matrix_ops.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

// mask
template<typename T>
nd::matrix<bool> nd::matrix<T>::operator ==(const T &val) {

	nd::matrix<bool> result(this->shape());

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<bool>(
				*this->data[i] == val);
	}

	return result;
}

// nd::matrix<T> == nd::matrix<T>
template<typename T>
bool nd::matrix<T>::operator ==(const nd::matrix<T> &mat) {

	nd::matrix<T> temp = std::move(mat);

	if (this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	for (big_size_t i = 0; i < this->size(); i++) {
		if ((*this->data[i]) != (*temp.data[i])) {
			return false;
		}
	}

	return true;
}

// nd::matrix<T> + nd::matrix<T>
template<typename T>
nd::matrix<T> nd::matrix<T>::operator +(const nd::matrix<T> &mat) {

	nd::matrix<T> temp = std::move(mat);

	if (this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	nd::matrix<T> result(this->shape());

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(
				(*this->data[i]) + (*temp.data[i]));
	}

	return result;
}

// nd::matrix<T> += nd::matrix<T>
template<typename T>
nd::matrix<T>& nd::matrix<T>::operator +=(const nd::matrix<T> &mat) {

	nd::matrix<T> temp = std::move(mat);

	if (this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] += (*temp.data[i]);
	}

	return (*this);
}

// nd::matrix<T> + val
template<typename T>
nd::matrix<T> nd::matrix<T>::operator +(const T &val) {

	nd::matrix<T> result(this->shape());

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(*this->data[i] + val);
	}

	return result;
}

// matrix<T> += val
template<typename T>
nd::matrix<T>& nd::matrix<T>::operator +=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] += val;
	}

	return (*this);
}

// ===========================

// nd::matrix<T> - nd::matrix<T>
template<typename T>
nd::matrix<T> nd::matrix<T>::operator -(const nd::matrix<T> &mat) {

	nd::matrix<T> temp = std::move(mat);

	if (this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}
	nd::matrix<T> result(this->shape());

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(
				(*this->data[i]) - (*temp.data[i]));
	}

	return result;
}

// nd::matrix<T> -= nd::matrix<T>
template<typename T>
nd::matrix<T>& nd::matrix<T>::operator -=(const nd::matrix<T> &mat) {

	nd::matrix<T> temp = std::move(mat);

	if (this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] -= (*temp.data[i]);
	}

	return (*this);
}

// nd::matrix<T> - val
template<typename T>
nd::matrix<T> nd::matrix<T>::operator -(const T &val) {

	nd::matrix<T> result(this->shape()); // 2-path, have to be modified

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(*this->data[i] - val);
	}

	return result;
}

// matrix<T> -= val
template<typename T>
nd::matrix<T>& nd::matrix<T>::operator -=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] -= val;
	}

	return (*this);
}

// ==================

// nd::matrix<T> * nd::matrix<T>
template<typename T>
nd::matrix<T> nd::matrix<T>::operator *(const nd::matrix<T> &mat) {

	nd::matrix<T> temp = std::move(mat);

	if (this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}
	nd::matrix<T> result(this->shape()); // 2-path, have to be modified

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(
				(*this->data[i]) * (*temp.data[i]));
	}

	return result;
}

// nd::matrix<T> *= nd::matrix<T>
template<typename T>
nd::matrix<T>& nd::matrix<T>::operator *=(const nd::matrix<T> &mat) {

	nd::matrix<T> temp = std::move(mat);

	if (this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] *= (*temp.data[i]);
	}

	return (*this);
}

// nd::matrix<T> * val
template<typename T>
nd::matrix<T> nd::matrix<T>::operator *(const T &val) {

	nd::matrix<T> result(this->shape()); // 2-path, have to be modified

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(*this->data[i] * val);
	}

	return result;
}

// matrix<T> *= val
template<typename T>
nd::matrix<T>& nd::matrix<T>::operator *=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] *= val;
	}

	return (*this);
}

// ============

// nd::matrix<T> / val
template<typename T>
nd::matrix<T> nd::matrix<T>::operator /(const T &val) {

	nd::matrix<T> result(this->shape());

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(*this->data[i] / val);
	}

	return result;
}

// matrix<T> /= val
template<typename T>
nd::matrix<T>& nd::matrix<T>::operator /=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] /= val;
	}

	return (*this);
}

template<typename T>
nd::matrix<T> nd::matrix<T>::operator [](max_size_t d_index) {

	max_size_t step = this->strides()[0];

	if (d_index >= this->shape()[0] || this->size() == this->step_size()) {

		throw nd::exception("nd_matrix - Index Out Of Range");

	} else {

		shape_t cur_shape = this->shape();

		shape_t new_shape(cur_shape.begin() + 1, cur_shape.end());
		coords new_attr(new_shape, false);

		vec1d<ref_t<T>> chunk_data;
		chunk_data.resize(attr.size1d);

		this->chunk_at(chunk_data, (d_index * step), ((d_index + 1) * step));

		nd::matrix<T> chunked_matrix(std::move(new_attr),
				std::move(chunk_data));

		return chunked_matrix;
	}
}

template<typename T>
void nd::matrix<T>::assign(shape_t indices, T val) {

	big_size_t index = this->index_at(indices);

	*this->data[index] = val;
}

template<typename T>
void nd::matrix<T>::_prem(shape_t axes) {

	if (axes.size() != this->ndim()) {

		throw nd::exception(
				"Invalid number of axes, axes.size() != mat.ndim()");
	}

	shape_t swaped_shape(this->ndim());
	shape_t swaped_strides(this->ndim());

	shape_t cur_shape = this->shape();
	shape_t cur_strides = this->strides();

	for (max_size_t i = 0; i < axes.size(); i++) {

		if (axes[i] >= this->ndim()) {

			throw nd::exception("Invalid axes, axes[i] >= mat.ndim()");
		}

		swaped_shape[i] = cur_shape[axes[i]];
		swaped_strides[i] = cur_strides[axes[i]];
	}

	this->attr.shape = swaped_shape;
	this->attr.nd_strides = swaped_strides;
}
