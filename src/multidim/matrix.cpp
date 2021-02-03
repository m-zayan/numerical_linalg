/*
 * matrix.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix_alloc.cpp"
#include "./matrix_iter.cpp"
#include "./matrix_ops.cpp"
#include "./matrix_stdout.cpp"

template<typename T>
big_size_t nd::matrix<T>::size() {
	return this->attr.size1d;
}

template<typename T>
shape_t nd::matrix<T>::shape() {

	return this->attr.shape;
}

template<typename T>
shape_t nd::matrix<T>::strides() {

	return this->attr.nd_strides;
}

template<typename T>
max_size_t nd::matrix<T>::ndim() {

	return this->attr.ndim;
}

template<typename T>
max_size_t nd::matrix<T>::step_size() {

	return this->shape()[this->ndim() - 1];
}

template<typename T>
bool nd::matrix<T>::own_data() {

	return this->attr.own_data;
}

template<typename T>
const_iterator<ref_t<T>> nd::matrix<T>::begin() {

	return this->data.begin();
}

template<typename T>
const_iterator<ref_t<T>> nd::matrix<T>::end() {

	return this->data.end();
}

template<typename T>
coords nd::matrix<T>::_m_attr() const {

	return this->attr;
}
