/*
 * matrix.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix_alloc.cpp"
#include "./matrix_ops.cpp"
#include "./matrix_init.cpp"
#include "./matrix_numeric.cpp"
#include "./matrix_stdout.cpp"

// base
template<typename T, bool ref_holder>
big_size_t nd::_matrix<T, ref_holder>::size() const {
	return this->attr.size1d;
}

template<typename T, bool ref_holder>
shape_t nd::_matrix<T, ref_holder>::shape() const {

	return this->attr.shape;
}

template<typename T, bool ref_holder>
strides_t nd::_matrix<T, ref_holder>::strides() const {

	return this->attr.strides;
}

template<typename T, bool ref_holder>
max_size_t nd::_matrix<T, ref_holder>::ndim() const {

	return this->attr.ndim;
}

template<typename T, bool ref_holder>
max_size_t nd::_matrix<T, ref_holder>::step_size() const {

	// scalar-like nd::matrix<T, ...>
	if (this->ndim() == 0) {
		return 0;
	}

	return this->shape()[this->ndim() - 1];
}

template<typename T, bool ref_holder>
bool nd::_matrix<T, ref_holder>::own_data() const {

	return this->attr.own_data;
}

template<typename T, bool ref_holder>
coords nd::_matrix<T, ref_holder>::_m_coords() const {

	return this->attr;
}

template<typename T, bool ref_holder>
big_size_t nd::_matrix<T, ref_holder>::_m_c_begin() const {

	return this->c_begin;
}

template<typename T, bool ref_holder>
big_size_t nd::_matrix<T, ref_holder>::_m_c_end() const {

	return this->c_end;
}

template<typename T, bool ref_holder>
IteratorType nd::_matrix<T, ref_holder>::_m_iter_type() const {

	return this->attr.iter_type;
}

template<typename T, bool ref_holder>
_type::data_t<T, ref_holder> nd::_matrix<T, ref_holder>::_m_ptr() const {

	return this->data;
}

template<typename T, bool ref_holder>
vec1d<T> nd::_matrix<T, ref_holder>::_m_data() const {

	return *(this->data.get());
}

template<typename T, bool ref_holder>
T* nd::_matrix<T, ref_holder>::_m_begin() {

	return &(*this->data.get())[0] + this->c_begin;
}

template<typename T, bool ref_holder>
T* nd::_matrix<T, ref_holder>::_m_end() {

	return &(*this->data.get())[0] + this->c_end;
}

template<typename T, bool ref_holder>
T& nd::_matrix<T, ref_holder>::at(shape_t indices) {

	big_size_t index = nd::iterator::nd_index_at(this->attr, indices);

	return (*this->data.get())[index];
}
