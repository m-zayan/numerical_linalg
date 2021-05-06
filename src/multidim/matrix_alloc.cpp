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
template<typename RT, bool ref_h>
nd::matrix<RT, ref_h>* nd::_matrix<T, ref_holder>::_m_dynamic_cast() {

	return dynamic_cast<nd::matrix<RT, ref_holder>*>(this);
}

template<typename T, bool ref_holder>
nd::_matrix<T, ref_holder>::~_matrix() {

}

template<typename T, bool ref_holder>
uflag8_t nd::_matrix<T, ref_holder>::_m_validate_op(const coords &attr0,
		const coords &attr1) {

	uflag8_t valid = (attr0.shape & attr1.shape);

	if (!valid) {

		throw nd::exception("Invalid element-wise operation, "
				"matrices must have the same shape");

	}

	else if (valid == 1) {

		return 1;
	}

	// case: valid = 2, (i.e. broadcastable)
	else if (nd::state::BroadcastingLevel == 0) {

		throw nd::exception("nd::state::BroadcastingLevel = 0, "
				"Broadcasting in not allowed");
	}

	// case: valid = 2, (i.e. broadcastable)
	else if (attr0.ndim != attr1.ndim && nd::state::BroadcastingLevel != 2) {

		throw nd::exception("nd::state::BroadcastingLevel = 1, "
				"Padding for nd::matrix::shape() should be explicitly defined");

	}

	else {
		return 2;
	}
}

template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::copy() {

	nd::matrix<T> result(this->shape());

	T *d = this->_m_begin();
	T *res = result._m_begin();

	_m_ops::copy<T, T>(res, d, this->_m_coords(), result._m_coords());

	return result;
}

template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::_m_alloc_if_broadcastable(
		coords attr0, coords attr1) {

	uflag8_t op_state = nd::_matrix<T, true>::_m_validate_op(attr0, attr1);

	coords new_attr;

	if (op_state == 1) {

		// attr0.shape == attr1.shape
		new_attr = coords(attr0.shape);
	}

	else {
		new_attr = nd::iterator::align_dim(attr0, attr1);
	}

	nd::matrix<T> result(new_attr);

	return result;

}

template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::_m_alloc_if_broadcastable(
		coords attr0, coords attr1, T val) {

	uflag8_t op_state = nd::_matrix<T, true>::_m_validate_op(attr0, attr1);

	coords new_attr;

	if (op_state == 1) {

		// attr0.shape == attr1.shape
		new_attr = coords(attr0.shape);
	}

	else {

		new_attr = nd::iterator::align_dim(attr0, attr1);
	}

	nd::matrix<T> result(new_attr, val);

	return result;
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
nd::matrix<T, true>::matrix(const coords &attr, T val) {

	this->attr = attr;
	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size(), val));

	this->c_begin = 0;
	this->c_end = this->size();
}

template<typename T>
nd::matrix<T, true>::matrix(const coords &attr) {

	this->attr = attr;
	this->attr.own_data = true;

	this->c_begin = 0;
	this->c_end = this->size();

	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size()));
}

template<typename T>
nd::matrix<T, true>::matrix(const nd::matrix<T> &mat) {

	nd::matrix<T, false> temp = mat;

	this->attr = temp._m_coords();
	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size()));

	this->c_begin = 0;
	this->c_end = this->size();

	T *d = temp._m_begin();
	T *res = this->_m_begin();

	_m_ops::copy<T, T>(res, d, mat._m_coords(), this->attr);
}

template<typename T>
nd::matrix<T, true>::matrix(const nd::matrix<T, false> &mat) {

	nd::matrix<T, false> temp = mat;

	this->attr = coords(temp.shape());
	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size()));

	this->c_begin = 0;
	this->c_end = this->size();

	T *d = temp._m_begin();
	T *res = this->_m_begin();

	_m_ops::copy<T, T>(res, d, mat._m_coords(), this->attr);
}

template<typename T>
nd::matrix<T, true>::~matrix() {

}

// false
template<typename T>
nd::matrix<T, false>::matrix(const coords &attr, shared_ptr<vec1d<T>> data,
		big_size_t c_begin, big_size_t c_end) {

	if (attr.own_data || c_begin > c_end) {

		// Debugging
		throw nd::exception("Invalid construction, "
				"for a non-reference holder nd::matrix<T, ...>");
	}

	this->attr = attr;

	this->data = data;

	this->c_begin = c_begin;
	this->c_end = c_end;
}

template<typename T>
nd::matrix<T, false>::matrix(const coords &attr, weak_ptr<vec1d<T>> data,
		big_size_t c_begin, big_size_t c_end) {

	if (attr.own_data || c_begin > c_end) {

		// Debugging
		throw nd::exception("Invalid construction, "
				"for a non-reference holder nd::matrix<T, ...>");
	}

	this->attr = attr;

	this->data = data;

	this->c_begin = c_begin;
	this->c_end = c_end;
}

template<typename T>
nd::matrix<T, false>::matrix(const nd::matrix<T, true> &mat) {

	this->attr = mat._m_coords();
	this->data = mat._m_ptr();

	this->c_begin = mat._m_c_begin();
	this->c_end = mat._m_c_end();
}

template<typename T>
nd::matrix<T, false>::matrix(const nd::matrix<T, false> &mat) {

	this->attr = mat._m_coords();
	this->data = mat._m_ptr();

	this->c_begin = mat._m_c_begin();
	this->c_end = mat._m_c_end();
}

template<typename T>
nd::matrix<T, false>::~matrix() {

}

