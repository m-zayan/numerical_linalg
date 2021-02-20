/*
 * matrix_ops.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

template<typename T, bool ref_holder>
template<typename U, typename RT>
void nd::_matrix<T, ref_holder>::_m_data_wrapper(U *d0, RT *d1, big_size_t s1,
		big_size_t c_begin, big_size_t c_end,
		std::function<void(U&, RT&)> func) {

	if (c_begin > c_end || c_end - c_begin >= s1) {

		// debugging
		nd::exception("nd::_matrix<T, ...>::_m_data_wrapper(...), "
				"size doesn't match");
	}

	for (big_size_t i = c_begin; i < c_end; i++) {

		func(d0[i], d1[i]);
	}
}

template<typename T, bool ref_holder>
void nd::_matrix<T, ref_holder>::_m_write_in_range(big_size_t c_begin,
		big_size_t c_end, std::function<void(T&)> func) {

	if (c_begin > c_end || c_end - c_begin >= this->size()) {

		// debugging
		nd::exception("nd::_matrix<T, ...>::_m_write_in_range(...), "
				"size doesn't match");
	}

	(*this->data.get()).write_in_range(c_begin, c_end, func);
}

// assign
template<typename T, bool ref_holder>
template<bool ref_h>
nd::matrix<T, false>& nd::_matrix<T, ref_holder>::operator =(
		const matrix<T, ref_h> &mat) {

	this->attr = mat._m_coords();

	this->data = data;

	this->attr.own_data = false;

	return *this->_m_dynamic_cast<T>();
}

// mask
template<typename T, bool ref_holder>
nd::matrix<min_size_t> nd::_matrix<T, ref_holder>::operator ==(const T &val) {

	nd::matrix<min_size_t> result(this->shape());

	T *d0 = this->_m_begin();
	min_size_t *d1 = result._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d1[i] = static_cast<min_size_t>(d0[i] == val);
	}

	return result;
}

// nd::matrix<T> == nd::matrix<T>
template<typename T, bool ref_holder>
template<bool ref_h>
bool nd::_matrix<T, ref_holder>::operator ==(const matrix<T, ref_h> &mat) {

	nd::matrix<T, false> temp = mat;

	if (this->ndim() != temp.ndim() || this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	T *d0 = this->_m_begin();
	T *d1 = temp._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {
		if (d0[i] != d1[i]) {
			return false;
		}
	}

	return true;
}

// nd::matrix<T> + nd::matrix<T>
template<typename T, bool ref_holder>
template<bool ref_h>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator +(
		const matrix<T, ref_h> &mat) {

	nd::matrix<T, false> temp = mat;

	if (this->ndim() != temp.ndim() || this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = temp._m_begin();

	T *d2 = result._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d2[i] = d0[i] + d1[i];
	}

	return result;
}

// nd::matrix<T> -= nd::matrix<T>
template<typename T, bool ref_holder>
template<bool ref_h>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator +=(
		const matrix<T, ref_h> &mat) {

	nd::matrix<T, false> temp = mat;

	if (this->ndim() != temp.ndim() || this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	T *d0 = this->_m_begin();
	T *d1 = temp._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d0[i] += d1[i];
	}

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> - val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator +(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d1[i] = d0[i] + val;
	}

	return result;
}

// matrix<T> -= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator +=(
		const T &val) {

	this->_m_write_in_range(this->c_begin, this->c_end,
			_ops::v1v::add<T, T>(val));

	return *this->_m_dynamic_cast<T>();
}

// ===========================

// nd::matrix<T> - nd::matrix<T>
template<typename T, bool ref_holder>
template<bool ref_h>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator -(
		const matrix<T, ref_h> &mat) {

	nd::matrix<T, false> temp = mat;

	if (this->ndim() != temp.ndim() || this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = temp._m_begin();
	T *d2 = result._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d2[i] = d0[i] - d1[i];
	}

	return result;
}

// nd::matrix<T> -= nd::matrix<T>
template<typename T, bool ref_holder>
template<bool ref_h>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator -=(
		const matrix<T, ref_h> &mat) {

	nd::matrix<T, false> temp = mat;

	if (this->ndim() != temp.ndim() || this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	T *d0 = this->_m_begin();
	T *d1 = temp._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d0[i] -= d1[i];
	}

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> - val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator -(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d1[i] = d0[i] - val;
	}

	return result;
}

// matrix<T> -= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator -=(
		const T &val) {

	this->_m_write_in_range(this->c_begin, this->c_end,
			_ops::v1v::sub<T, T>(val));

	return *this->_m_dynamic_cast<T>();
}

// ==================

// nd::matrix<T> * nd::matrix<T>
template<typename T, bool ref_holder>
template<bool ref_h>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator *(
		const matrix<T, ref_h> &mat) {

	nd::matrix<T, false> temp = mat;

	if (this->ndim() != temp.ndim() || this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = temp._m_begin();
	T *d2 = result._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d2[i] = d0[i] * d1[i];
	}

	return result;
}

// nd::matrix<T> *= nd::matrix<T>
template<typename T, bool ref_holder>
template<bool ref_h>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator *=(
		const matrix<T, ref_h> &mat) {

	nd::matrix<T, false> temp = mat;

	if (this->ndim() != temp.ndim() || this->shape() != temp.shape()) {
		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");
	}

	T *d0 = this->_m_begin();
	T *d1 = temp._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d0[i] *= d1[i];
	}

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> * val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator *(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d1[i] = d0[i] * val;
	}

	return result;
}

// matrix<T> *= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator *=(
		const T &val) {

	this->_m_write_in_range(this->c_begin, this->c_end,
			_ops::v1v::mul<T, T>(val));

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> / val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator /(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	for (big_size_t i = 0; i < this->size(); i++) {

		d1[i] = d0[i] / val;
	}

	return result;
}

// matrix<T> /= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator /=(
		const T &val) {

	this->_m_write_in_range(this->c_begin, this->c_end,
			_ops::v1v::div<T, T>(val));

	return *this->_m_dynamic_cast<T>();
}

template<typename T, bool ref_holder>
nd::matrix<T, false> nd::_matrix<T, ref_holder>::operator [](
		max_size_t d_index) {

	max_size_t step = this->strides()[0];

	if (d_index >= this->shape()[0] || this->size() == this->step_size()) {

		throw nd::exception("nd::matrix<T> - Index Out Of Range");

	} else {

		shape_t cur_shape = this->shape();

		shape_t new_shape(cur_shape.begin() + 1, cur_shape.end());
		coords new_attr(new_shape, false);

		big_size_t c_begin = this->c_begin + (d_index * step);
		big_size_t c_end = this->c_begin + (d_index + 1) * step;

		nd::matrix<T, false> mat_chunk(new_attr, this->data, c_begin, c_end);

		return mat_chunk;
	}
}

template<typename T, bool ref_holder>
void nd::_matrix<T, ref_holder>::assign(shape_t indices, T val) {

	RandomAccessNdIterator rndIter(this->attr);

	big_size_t index = rndIter.index_at(indices);

	(*this->data)[index] = val;
}

template<typename T, bool ref_holder>
nd::matrix<T, false> nd::_matrix<T, ref_holder>::permute(shape_t axes) {

	if (axes.size() != this->ndim()) {

		throw nd::exception(
				"Invalid number of axes, axes.size() != this->ndim()");
	}

	shape_t swaped_shape(this->ndim());
	shape_t swaped_strides(this->ndim());

	shape_t cur_shape = this->shape();
	shape_t cur_strides = this->strides();

	for (max_size_t i = 0; i < axes.size(); i++) {

		if (axes[i] >= this->ndim()) {

			throw nd::exception("Invalid axes, axes[i] >= this->ndim()");
		}

		swaped_shape[i] = cur_shape[axes[i]];
		swaped_strides[i] = cur_strides[axes[i]];
	}

	coords new_attr(swaped_shape, swaped_strides, false);

	nd::matrix<T, false> mat_chunk(new_attr, this->data, 0, this->size());

	return mat_chunk;
}

// false
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::reordered_chunk(bool use_iter) {

	nd::matrix<T> mat_chunk(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = mat_chunk._m_begin();

	if (use_iter) {

		RandomAccessNdIterator rndIter(this->attr);

		for (big_size_t i = 0; i < this->size(); i++) {

			d1[i] = d0[rndIter.index_at(i)];
		}
	}

	else {

		for (big_size_t i = 0; i < this->size(); i++) {

			d1[i] = d0[i];
		}
	}

	return mat_chunk;
}

