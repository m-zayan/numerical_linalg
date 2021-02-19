/*
 * matrix.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix_alloc.cpp"
#include "./matrix_ops.cpp"
#include "./matrix_stdout.cpp"

// base

template<typename T, bool shared_ref>
big_size_t nd::_matrix<T, shared_ref>::size() {
	return this->attr.size1d;
}

template<typename T, bool shared_ref>
shape_t nd::_matrix<T, shared_ref>::shape() {

	return this->attr.shape;
}

template<typename T, bool shared_ref>
shape_t nd::_matrix<T, shared_ref>::strides() {

	return this->attr.strides;
}

template<typename T, bool shared_ref>
max_size_t nd::_matrix<T, shared_ref>::ndim() {

	return this->attr.ndim;
}

template<typename T, bool shared_ref>
max_size_t nd::_matrix<T, shared_ref>::step_size() {

	return this->shape()[this->ndim() - 1];
}

template<typename T, bool shared_ref>
bool nd::_matrix<T, shared_ref>::own_data() {

	return this->attr.own_data;
}

template<typename T, bool shared_ref>
coords nd::_matrix<T, shared_ref>::_m_coords() const {

	return this->attr;
}

template<typename T, bool shared_ref>
vec1d<T> nd::_matrix<T, shared_ref>::_m_data() const {

	return *this->data.get();
}

template<typename T, bool shared_ref>
big_size_t nd::_matrix<T, shared_ref>::_m_c_begin() const {

	return this->c_begin;
}

template<typename T, bool shared_ref>
big_size_t nd::_matrix<T, shared_ref>::_m_c_end() const {

	return this->c_end;
}

template<typename T, bool shared_ref>
T* nd::_matrix<T, shared_ref>::_m_begin() {

	return &(*this->data.get())[0] + this->c_begin;
}

template<typename T, bool shared_ref>
T* nd::_matrix<T, shared_ref>::_m_end() {

	return &(*this->data.get())[0] + this->c_end;
}

