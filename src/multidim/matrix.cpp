/*
 * matrix.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix_alloc.cpp"
#include "./matrix_iter.cpp"
#include "./matrix_ops.cpp"
#include "./matrix_stdout.cpp"

template<typename T, bool shared_ref>
big_size_t nd::matrix<T, shared_ref>::size() {
	return this->attr.size1d;
}

template<typename T, bool shared_ref>
shape_t nd::matrix<T, shared_ref>::shape() {

	return this->attr.shape;
}

template<typename T, bool shared_ref>
shape_t nd::matrix<T, shared_ref>::strides() {

	return this->attr.nd_strides;
}

template<typename T, bool shared_ref>
max_size_t nd::matrix<T, shared_ref>::ndim() {

	return this->attr.ndim;
}

template<typename T, bool shared_ref>
max_size_t nd::matrix<T, shared_ref>::step_size() {

	return this->shape()[this->ndim() - 1];
}

template<typename T, bool shared_ref>
bool nd::matrix<T, shared_ref>::own_data() {

	return this->attr.own_data;
}

//template<typename T, bool shared_ref>
//const_iterator<data_t<T>> nd::matrix<T, shared_ref>::begin() {
//
//	return this->data.begin();
//}
//
//template<typename T, bool shared_ref>
//const_iterator<data_t<T>> nd::matrix<T, shared_ref>::end() {
//
//	return this->data.end();
//}

template<typename T, bool shared_ref>
coords nd::matrix<T, shared_ref>::_m_attr() const {

	return this->attr;
}
