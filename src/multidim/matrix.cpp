/*
 * matrix.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix_alloc.cpp"
#include "./matrix_ops.cpp"
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
shape_t nd::_matrix<T, ref_holder>::strides() const {

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

	nd::iterator::RandomAccess rndIter(this->attr);

	big_size_t index = rndIter.nd_index_at(indices);

	return (*this->data.get())[index];

}

// ufunc
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

template<typename T>
nd::matrix<T> nd::random::uniform(T low, T high, shape_t shape) {

	nd::matrix<T> mat(shape);

	T *d = mat._m_begin();

	auto generator_wrapper = generator::random_uniform<T>(low, high);

	for (big_size_t i = 0; i < mat.size(); i++) {

		d[i] = generator_wrapper();
	}

	return mat;
}

