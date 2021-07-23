/*
 * matrix_ops.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

// nd::matrix<T> = val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator =(
		const T &val) {

	T *d = this->_m_begin();

	_m_ops::contiguous_write_vec_val(d, val, this->attr,
			_v_ops::istatic_cast<T, T>);

	return *this->_m_dynamic_cast<T>();
}

// mask
template<typename T, bool ref_holder>
nd::matrix<mask_t> nd::_matrix<T, ref_holder>::operator ==(const T &val) {

	nd::matrix<mask_t> result(this->shape());

	T *d0 = this->_m_begin();
	mask_t *d1 = result._m_begin();

	_m_ops::write_vec_val_vec<mask_t, T, T>(d1, d0, val, this->attr,
			result._m_coords(), _v_ops::bool_equal<mask_t, T, T>);

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

	coords attr0 = this->attr;
	coords attr1 = temp._m_coords();

	nd::matrix<T> result = nd::_matrix<T, true>::_m_alloc_if_broadcastable(
			attr0, attr1, 0);

	T *d0 = this->_m_begin();
	T *d1 = temp._m_begin();

	T *d2 = result._m_begin();

	_m_ops::write_vec_vec_vec<T, T, T>(d2, d0, d1, attr0, attr1,
			result._m_coords(), _v_ops::add<T, T, T>);

	result._m_clear_iter_type();

	return result;
}

// ### nd::matrix<T> -= nd::matrix<T> | must be modified <--> broadcastable
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

	_m_ops::write_vec_vec(d0, d1, this->attr, mat._m_coords(),
			_v_ops::add<T, T, T>);

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> - val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator +(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	_m_ops::write_vec_val_vec<T, T, T>(d1, d0, val, this->attr,
			result._m_coords(), _v_ops::add<T, T, T>);

	return result;

}

// matrix<T> -= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator +=(
		const T &val) {

	T *d = this->_m_begin();

	_m_ops::write_val_vec<T, T>(d, val, this->attr, _v_ops::add<T, T, T>);

	return *this->_m_dynamic_cast<T>();
}

// ===========================

// nd::matrix<T> - nd::matrix<T>
template<typename T, bool ref_holder>
template<bool ref_h>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator -(
		const matrix<T, ref_h> &mat) {

	nd::matrix<T, false> temp = mat;

	coords attr0 = this->attr;
	coords attr1 = temp._m_coords();

	nd::matrix<T> result = nd::_matrix<T, true>::_m_alloc_if_broadcastable(
			attr0, attr1, 0);

	T *d0 = this->_m_begin();
	T *d1 = temp._m_begin();

	T *d2 = result._m_begin();

	_m_ops::write_vec_vec_vec<T, T, T>(d2, d0, d1, attr0, attr1,
			result._m_coords(), _v_ops::sub<T, T, T>);

	result._m_clear_iter_type();

	return result;
}

// ### nd::matrix<T> -= nd::matrix<T> | must be modified <--> broadcastable
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

	_m_ops::write_vec_vec(d0, d1, this->attr, mat._m_coords(),
			_v_ops::sub<T, T, T>);

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> - val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator -(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	_m_ops::write_vec_val_vec<T, T, T>(d1, d0, val, this->attr,
			result._m_coords(), _v_ops::sub<T, T, T>);

	return result;

}

// matrix<T> -= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator -=(
		const T &val) {

	T *d = this->_m_begin();

	_m_ops::write_val_vec<T, T, T>(d, val, this->attr, _v_ops::sub<T, T, T>);

	return *this->_m_dynamic_cast<T>();
}

// ==================

// nd::matrix<T> * nd::matrix<T>
template<typename T, bool ref_holder>
template<typename U, bool ref_h>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator *(
		const matrix<U, ref_h> &mat) {

	nd::matrix<U, false> temp = mat;

	coords attr0 = this->attr;
	coords attr1 = temp._m_coords();

	nd::matrix<T> result = nd::_matrix<T, true>::_m_alloc_if_broadcastable(
			attr0, attr1, 0);

	T *d0 = this->_m_begin();
	U *d1 = temp._m_begin();

	T *d2 = result._m_begin();

	_m_ops::write_vec_vec_vec<T, T, U>(d2, d0, d1, attr0, attr1,
			result._m_coords(), _v_ops::mul<T, T, U>);

	result._m_clear_iter_type();

	return result;
}

// ### nd::matrix<T> *= nd::matrix<T> | must be modified <--> broadcastable
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

	_m_ops::write_vec_vec<T, T>(d0, d1, this->attr, mat._m_coords(),
			_v_ops::mul<T, T, T>);

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> * val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator *(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	_m_ops::write_vec_val_vec<T, T, T>(d1, d0, val, this->attr,
			result._m_coords(), _v_ops::mul<T, T, T>);

	return result;
}

// matrix<T> *= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator *=(
		const T &val) {

	T *d = this->_m_begin();

	_m_ops::write_val_vec<T, T>(d, val, this->attr, _v_ops::mul<T, T, T>);

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> / val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator /(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	_m_ops::write_vec_val_vec<T, T, T>(d1, d0, val, this->attr,
			result._m_coords(), _v_ops::div<T, T, T>);

	return result;
}

// matrix<T> /= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator /=(
		const T &val) {

	T *d = this->_m_begin();

	_m_ops::write_val_vec<T, T>(d, val, this->attr, _v_ops::div<T, T, T>);

	return *this->_m_dynamic_cast<T>();
}

template<typename T, bool ref_holder>
nd::matrix<T, false> nd::_matrix<T, ref_holder>::operator [](
		max_size_t d_index) {

	if (this->ndim() == 0) {

		throw nd::exception("nd::matrix<T> - N-Dim-Index Out Of Range");
	}

	else if (d_index >= this->shape()[0]) {

		throw nd::exception("nd::matrix<T> - Dim-Index Out Of Range");
	}

	max_size_t step = this->strides()[0];

	// case: scalar-like nd::matrix<T>
	if (this->ndim() == 1) {

		coords chunk_attr(false);

		big_size_t c_begin = this->c_begin + (d_index * step);
		big_size_t c_end = this->c_begin + (d_index + 1) * step;

		nd::matrix<T, false> mat_chunk(chunk_attr, this->data, c_begin, c_end);

		return mat_chunk;
	}

	else {

		shape_t chunk_shape = this->shape().slice(1, this->ndim());
		strides_t chunk_strides = this->strides().slice(1, this->ndim());

		coords chunk_attr(chunk_shape, chunk_strides, false,
				this->attr.iter_type);

		big_size_t c_begin = this->c_begin + (d_index * step);
		big_size_t c_end = this->c_end;

		nd::matrix<T, false> mat_chunk(chunk_attr, this->data, c_begin, c_end);

		return mat_chunk;
	}
}

template<typename T, bool ref_holder>
nd::matrix<T, false> nd::_matrix<T, ref_holder>::slice(shape_t begin,
		shape_t end) {

	adjust_slice(this->attr, begin, end);

	coords chunk_attr = this->attr.slice(begin, end);

	big_size_t c_begin = nd::iterator::nd_index_at(this->attr, begin);
	big_size_t c_end = nd::iterator::nd_index_at(this->attr, chunk_attr.shape);

	nd::matrix<T, false> mat_chunk(chunk_attr, this->data, c_begin, c_end);

	return mat_chunk;

}

template<typename T, bool ref_holder>
void nd::_matrix<T, ref_holder>::assign(shape_t indices, T val) {

	big_size_t index = nd::iterator::nd_index_at(this->attr, indices);

	(*this->data.get())[index] = val;
}

template<typename T, bool ref_holder>
nd::matrix<T, false> nd::_matrix<T, ref_holder>::permute(shape_t axes) const {

	coords new_attr = this->attr.permuted(axes, false);

	nd::matrix<T, false> mat_chunk(new_attr, this->data, 0, this->size());

	return mat_chunk;
}

template<typename T, bool ref_holder>
nd::matrix<T, false> nd::_matrix<T, ref_holder>::reshape(shape_t shape) const {

	coords new_attr = coords(shape, false, this->attr.iter_type);

	if (new_attr.size1d != this->size()) {

		throw nd::exception("nd::matrix<T>::reshape(...), Invalid shape");

	}

	nd::matrix<T, false> mat_chunk(new_attr, this->data, 0, this->size());

	return mat_chunk;
}

template<typename T, bool ref_holder>
nd::matrix<T, false> nd::_matrix<T, ref_holder>::set_new_coords(
		const coords &attr) const {

	if (attr.own_data) {

		// Debugging
		throw nd::exception("Invalid coords::*, "
				"for a non-reference holder nd::matrix<T, ...>");
	}

	if (attr.size1d != this->size()) {

		// Debugging
		throw nd::exception("Invalid construction, "
				"coords::size(...) != nd::matrix<T, false>::size()");
	}

	nd::matrix<T, false> result(attr, this->data, this->c_begin, this->c_end);

	return result;
}

template<typename T, bool ref_holder>
nd::matrix<T, false> nd::_matrix<T, ref_holder>::op_view_2d() const {

	coords new_attr = this->attr.view3d(false);

	nd::matrix<T, false> result(new_attr, this->data, this->c_begin,
			this->c_end);

	return result;
}

template<typename T, bool ref_holder>
void nd::_matrix<T, ref_holder>::_m_reshape(shape_t shape) {

	coords new_attr = coords(shape);

	if (new_attr.size1d != this->size()) {

		throw nd::exception("nd::matrix<T>::_m_reshape(...), Invalid shape");

	}

	this->attr = new_attr;
}

template<typename T, bool ref_holder>
void nd::_matrix<T, ref_holder>::_m_clear_iter_type() {

	if (!is_scalar(this->attr)) {
		this->attr.iter_type = IteratorType::None;
	}
}

template<typename T, bool ref_holder>
template<typename RT>
nd::_matrix<T, ref_holder>::operator nd::matrix<RT>() const {

	nd::matrix<RT> result(this->shape());

	T *d = (*this->data.get()).ref(this->c_begin);
	RT *res = result._m_begin();

	_m_ops::copy<RT, T>(res, d, this->_m_coords(), result._m_coords());

	return result;
}

template<typename T, bool ref_holder>
template<typename RT>
nd::_matrix<T, ref_holder>::operator RT() const {

	if (!is_scalar(this->attr)) {

		throw nd::exception("invalid-cast, nd::matrix<T, ...>::ndim() > 0");
	}

	T *d = (*this->data.get()).ref(this->c_begin);

	return static_cast<RT>(d[0]);
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT> nd::apply(const nd::matrix<T, rf_h> &mat,
		std::function<RT(T)> func) {

	nd::matrix<T, false> tmp = mat;

	nd::matrix<RT> result(mat.shape());

	T *d = tmp._m_begin();
	RT *res = result._m_begin();

	_m_ops::write_vec<RT, T>(res, d, tmp._m_coords(), result._m_coords(), func);

	return result;
}

// ...
template<typename RT, typename T1, typename T2, bool rf_h>
nd::matrix<RT> nd::apply_along_axis(const nd::matrix<T1, rf_h> &mat,
		std::function<
				void(T2&, vec1d<max_size_t>&, vec1d<T1>&, max_size_t,
						max_size_t)> func, max_size_t axis, T2 initial_acc,
		std::function<RT(T2&)> ppfunc, bool reduce, bool keepdims) {

	nd::matrix<T1, false> tmp = mat;

	max_size_t ndim = tmp.ndim();

	if (axis >= ndim) {
		throw nd::exception("nd::matrix<T> - axis, Out of Range");
	}

	if (!reduce && keepdims) {

		// might set warning ...
	}

	coords attr = tmp._m_coords();

	coords tmp_attr = attr.swapaxes(ndim - 1, axis, false);

	max_size_t dim_size = attr.shape[axis];

	coords new_attr;

	if (reduce) {

		new_attr = attr.reduce(axis, keepdims);
	}

	else {

		new_attr = attr;

		dim_size = 1;
	}

	nd::matrix<RT> result(new_attr.shape);

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_iterator(tmp_attr);

	big_size_t out_size = tmp.size() / dim_size;

	max_size_t aux_size = nd::mem::clip_dim(dim_size);

	max_size_t vi;

	vec1d<T1> elems(aux_size);
	vec1d<max_size_t> indices(aux_size);

	T1 *d = tmp._m_begin();
	RT *res = result._m_begin();

	T2 acc;

	for (big_size_t i = 0; i < out_size; i++) {

		vi = 0;
		acc = initial_acc;

		for (max_size_t j = 0; j < dim_size; j++) {

			elems[vi] = d[it->index1d];
			indices[vi] = j;

			vi++;

			if (vi >= aux_size) {
				vi = 0;
				func(acc, indices, elems, 0, aux_size);
			}

			ITER_NEXT(it);
		}

		if (dim_size % aux_size) {

			func(acc, indices, elems, 0, vi);
		}

		res[i] = ppfunc(acc);
	}

	// [1]
	nd::iterator::free_iterator(it);

	return result;
}
