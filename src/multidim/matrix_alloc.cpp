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
nd::matrix<T> nd::_matrix<T, ref_holder>::copy() {

	nd::matrix<T> result(this->shape());

	T *d = this->_m_begin();
	T *res = result._m_begin();

	_m_ops::copy<T, T>(res, d, this->_m_coords(), this->req_iter);

	return result;
}

// true
template<typename T>
nd::matrix<T, true>::matrix(shape_t shape) {

	this->attr = coords(shape);
	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size()));

	this->c_begin = 0;
	this->c_end = this->size();

	this->req_iter = false;
}

template<typename T>
nd::matrix<T, true>::matrix(shape_t shape, T val) {

	this->attr = coords(shape);
	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size(), val));

	this->c_begin = 0;
	this->c_end = this->size();

	this->req_iter = false;
}

template<typename T>
nd::matrix<T, true>::matrix(const coords &attr) {

	this->attr = attr;
	this->attr.own_data = true;

	this->c_begin = 0;
	this->c_end = this->size();

	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size()));

	this->req_iter = false;
}

template<typename T>
nd::matrix<T, true>::matrix(const nd::matrix<T> &mat) {

	nd::matrix<T, false> temp = mat;

	this->attr = temp._m_coords();
	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size()));

	this->c_begin = 0;
	this->c_end = this->size();

	this->req_iter = false;

	T *d = temp._m_begin();
	T *res = this->_m_begin();

	_m_ops::copy<T, T>(res, d, mat._m_coords(), mat._m_req_iter());
}

template<typename T>
nd::matrix<T, true>::matrix(const nd::matrix<T, false> &mat) {

	nd::matrix<T, false> temp = mat;

	this->attr = coords(temp.shape());
	this->data = allocator::val_to_shared_ptr(vec1d<T>(this->size()));

	this->c_begin = 0;
	this->c_end = this->size();

	this->req_iter = false;

	T *d = temp._m_begin();
	T *res = this->_m_begin();

	_m_ops::copy<T, T>(res, d, mat._m_coords(), mat._m_req_iter());
}

template<typename T>
nd::matrix<T, true>::~matrix() {

}

// false
template<typename T>
nd::matrix<T, false>::matrix(const coords &attr, shared_ptr<vec1d<T>> data,
		big_size_t c_begin, big_size_t c_end, bool req_iter) {

	if (attr.own_data || c_begin > c_end) {

		// debuging
		throw nd::exception("Invalid construction, "
				"for a non-reference holder nd::matrix<T, ...>");
	}

	this->attr = attr;

	this->data = data;

	this->c_begin = c_begin;
	this->c_end = c_end;

	this->req_iter = req_iter;
}

template<typename T>
nd::matrix<T, false>::matrix(const coords &attr, weak_ptr<vec1d<T>> data,
		big_size_t c_begin, big_size_t c_end, bool req_iter) {

	if (attr.own_data || c_begin > c_end) {

		// debuging
		throw nd::exception("Invalid construction, "
				"for a non-reference holder nd::matrix<T, ...>");
	}

	this->attr = attr;

	this->data = data;

	this->c_begin = c_begin;
	this->c_end = c_end;

	this->req_iter = req_iter;
}

template<typename T>
nd::matrix<T, false>::matrix(const nd::matrix<T, true> &mat) {

	this->attr = mat._m_coords();
	this->data = mat._m_ptr();

	this->c_begin = mat._m_c_begin();
	this->c_end = mat._m_c_end();

	this->req_iter = mat._m_req_iter();
}

template<typename T>
nd::matrix<T, false>::matrix(const nd::matrix<T, false> &mat) {

	this->attr = mat._m_coords();
	this->data = mat._m_ptr();

	this->c_begin = mat._m_c_begin();
	this->c_end = mat._m_c_end();

	this->req_iter = mat._m_req_iter();
}

template<typename T>
nd::matrix<T, false>::~matrix() {

}

