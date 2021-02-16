/*
 * matrix_ops.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

// assign
template<typename T, bool shared_ref>
nd::matrix<T, false>& nd::matrix<T, shared_ref>::operator =(
		const matrix<T> &mat) {

	this->attr = mat._m_attr();

	// should be replaced by this->movedata()
	this->data.assign(mat.begin(), mat.end());

	this->attr.own_data = false;

	return (*this);
}

// mask
template<typename T, bool shared_ref>
nd::matrix<bool> nd::matrix<T, shared_ref>::operator ==(const T &val) {

	nd::matrix<bool> result(this->shape());

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<bool>(
				*this->data[i] == val);
	}

	return result;
}

// nd::matrix<T> == nd::matrix<T>
template<typename T, bool shared_ref>
bool nd::matrix<T, shared_ref>::operator ==(const nd::matrix<T> &mat) {

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
template<typename T, bool shared_ref>
nd::matrix<T> nd::matrix<T, shared_ref>::operator +(const nd::matrix<T> &mat) {

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
template<typename T, bool shared_ref>
nd::matrix<T>& nd::matrix<T, shared_ref>::operator +=(
		const nd::matrix<T> &mat) {

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
template<typename T, bool shared_ref>
nd::matrix<T> nd::matrix<T, shared_ref>::operator +(const T &val) {

	nd::matrix<T> result(this->shape());

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(*this->data[i] + val);
	}

	return result;
}

// matrix<T> += val
template<typename T, bool shared_ref>
nd::matrix<T>& nd::matrix<T, shared_ref>::operator +=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] += val;
	}

	return (*this);
}

// ===========================

// nd::matrix<T> - nd::matrix<T>
template<typename T, bool shared_ref>
nd::matrix<T> nd::matrix<T, shared_ref>::operator -(const nd::matrix<T> &mat) {

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
template<typename T, bool shared_ref>
nd::matrix<T>& nd::matrix<T, shared_ref>::operator -=(
		const nd::matrix<T> &mat) {

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
template<typename T, bool shared_ref>

nd::matrix<T> nd::matrix<T, shared_ref>::operator -(const T &val) {

	nd::matrix<T> result(this->shape());

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(*this->data[i] - val);
	}

	return result;
}

// matrix<T> -= val
template<typename T, bool shared_ref>
nd::matrix<T>& nd::matrix<T, shared_ref>::operator -=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] -= val;
	}

	return (*this);
}

// ==================

// nd::matrix<T> * nd::matrix<T>
template<typename T, bool shared_ref>
nd::matrix<T> nd::matrix<T, shared_ref>::operator *(const nd::matrix<T> &mat) {

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
template<typename T, bool shared_ref>
nd::matrix<T>& nd::matrix<T, shared_ref>::operator *=(
		const nd::matrix<T> &mat) {

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
template<typename T, bool shared_ref>
nd::matrix<T> nd::matrix<T, shared_ref>::operator *(const T &val) {

	nd::matrix<T> result(this->shape()); // 2-path, have to be modified

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(*this->data[i] * val);
	}

	return result;
}

// matrix<T> *= val
template<typename T, bool shared_ref>
nd::matrix<T>& nd::matrix<T, shared_ref>::operator *=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] *= val;
	}

	return (*this);
}

// ============

// nd::matrix<T> / val
template<typename T, bool shared_ref>
nd::matrix<T> nd::matrix<T, shared_ref>::operator /(const T &val) {

	nd::matrix<T> result(this->shape());

	for (big_size_t i = 0; i < this->size(); i++) {
		result.data[i] = allocator::val_to_shared_ptr<T>(*this->data[i] / val);
	}

	return result;
}

// matrix<T> /= val
template<typename T, bool shared_ref>
nd::matrix<T>& nd::matrix<T, shared_ref>::operator /=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		*this->data[i] /= val;
	}

	return (*this);
}

template<typename T, bool shared_ref>
nd::matrix<T, false> nd::matrix<T, shared_ref>::chunk_at(const coords &attr,
		big_size_t begin, big_size_t end) {

	RandomAccessNdIterator rndIter(attr);

	nd::matrix<T, false> mat_chunk(std::move(attr));

	for (big_size_t i = begin; i < end; i++) {
		mat_chunk.data[i - begin] = this->data[rndIter.index_at(i)];
	}

	return mat_chunk;
}

template<typename T, bool shared_ref>
nd::matrix<T, false> nd::matrix<T, shared_ref>::operator [](
		max_size_t d_index) {

	max_size_t step = this->strides()[0];

	if (d_index >= this->shape()[0] || this->size() == this->step_size()) {

		throw nd::exception("nd::matrix<T> - Index Out Of Range");

	} else {

		shape_t cur_shape = this->shape();

		shape_t new_shape(cur_shape.begin() + 1, cur_shape.end());
		coords new_attr(new_shape, false);

		big_size_t begin = (d_index * step);
		big_size_t end = (d_index + 1) * step;

		nd::matrix<T, false> mat_chunk = this->chunk_at(new_attr, begin, end);

		return mat_chunk;
	}
}

template<typename T, bool shared_ref>
void nd::matrix<T, shared_ref>::assign(shape_t indices, T val) {

	RandomAccessNdIterator rndIter(this->attr);

	big_size_t index = rndIter.index_at(indices);

	*this->data[index] = val;
}

template<typename T, bool shared_ref>
nd::matrix<T, false> nd::matrix<T, shared_ref>::permute(shape_t axes) {

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

	coords attr(swaped_shape, swaped_strides, false);

	nd::matrix<T, false> mat_chunk = this->chunk_at(attr, 0, this->size());

	return mat_chunk;
}
