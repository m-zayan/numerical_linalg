/*
 * matrix_ops.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

// mask
template<typename T, bool ref_holder>
nd::matrix<mask_t> nd::_matrix<T, ref_holder>::operator ==(const T &val) {

	nd::matrix<mask_t> result(this->shape());

	T *d0 = this->_m_begin();
	mask_t *d1 = result._m_begin();

	_m_ops::write_vec_val_vec<mask_t, T, T>(d1, d0, val, this->attr,
			_v_ops::bool_equal<mask_t, T, T>, this->req_iter);

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

	_m_ops::write_vec_vec_vec<T, T, T>(d2, d0, d1, this->attr, mat._m_coords(),
			_v_ops::add<T, T, T>, this->req_iter, mat._m_req_iter());

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

	_m_ops::write_vec_vec(d0, d1, this->attr, mat._m_coords(),
			_v_ops::add<T, T, T>, this->req_iter, mat._m_req_iter());

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> - val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator +(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	_m_ops::write_vec_val_vec<T, T, T>(d1, d0, val, this->attr,
			_v_ops::add<T, T, T>, this->req_iter);

	return result;

}

// matrix<T> -= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator +=(
		const T &val) {

	T *d = this->_m_begin();

	_m_ops::write_val_vec<T, T, T>(d, val, this->attr, _v_ops::add<T, T, T>,
			this->req_iter);

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

	_m_ops::write_vec_vec_vec<T, T, T>(d2, d0, d1, this->attr, mat._m_coords(),
			_v_ops::sub<T, T, T>, this->req_iter, mat._m_req_iter());

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

	_m_ops::write_vec_vec(d0, d1, this->attr, mat._m_coords(),
			_v_ops::sub<T, T, T>, this->req_iter, mat._m_req_iter());

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> - val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator -(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	_m_ops::write_vec_val_vec<T, T, T>(d1, d0, val, this->attr,
			_v_ops::sub<T, T, T>, this->req_iter);

	return result;

}

// matrix<T> -= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator -=(
		const T &val) {

	T *d = this->_m_begin();

	_m_ops::write_val_vec<T, T, T>(d, val, this->attr, _v_ops::sub<T, T, T>,
			this->req_iter);

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

	_m_ops::write_vec_vec_vec<T, T, T>(d2, d0, d1, this->attr, mat._m_coords(),
			_v_ops::mul<T, T, T>, this->req_iter, mat._m_req_iter());

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

	_m_ops::write_vec_vec<T, T>(d0, d1, this->attr, mat._m_coords(),
			_v_ops::mul<T, T, T>, this->req_iter, mat._m_req_iter());

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> * val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator *(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	_m_ops::write_vec_val_vec<T, T, T>(d1, d0, val, this->attr,
			_v_ops::mul<T, T, T>, this->req_iter);

	return result;
}

// matrix<T> *= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator *=(
		const T &val) {

	T *d = this->_m_begin();

	_m_ops::write_val_vec<T, T>(d, val, this->attr, _v_ops::mul<T, T, T>,
			this->req_iter);

	return *this->_m_dynamic_cast<T>();
}

// nd::matrix<T> / val
template<typename T, bool ref_holder>
nd::matrix<T> nd::_matrix<T, ref_holder>::operator /(const T &val) {

	nd::matrix<T> result(this->shape());

	T *d0 = this->_m_begin();
	T *d1 = result._m_begin();

	_m_ops::write_vec_val_vec<T, T, T>(d1, d0, val, this->attr,
			_v_ops::div<T, T, T>, this->req_iter);

	return result;
}

// matrix<T> /= val
template<typename T, bool ref_holder>
nd::matrix<T, ref_holder>& nd::_matrix<T, ref_holder>::operator /=(
		const T &val) {

	T *d = this->_m_begin();

	_m_ops::write_val_vec<T, T>(d, val, this->attr, _v_ops::div<T, T, T>,
			this->req_iter);

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

		nd::matrix<T, false> mat_chunk(new_attr, this->data, c_begin, c_end,
				false);

		return mat_chunk;
	}
}

template<typename T, bool ref_holder>
void nd::_matrix<T, ref_holder>::assign(shape_t indices, T val) {

	RandomAccessNdIterator rndIter(this->attr);

	big_size_t index = rndIter.index_at(indices);

	(*this->data.get())[index] = val;
}

template<typename T, bool ref_holder>
nd::matrix<T, false> nd::_matrix<T, ref_holder>::permute(shape_t axes) {

	coords new_attr = this->attr.permuted(axes, false);

	nd::matrix<T, false> mat_chunk(new_attr, this->data, 0, this->size(), true);

	return mat_chunk;
}

template<typename T, bool ref_holder>
nd::matrix<T, false> nd::_matrix<T, ref_holder>::reshape(shape_t shape) {

	coords new_attr = coords(shape);

	if (new_attr.size1d != this->size()) {

		throw nd::exception("nd::matrix<T>::reshape(...), Invalid shape");

	}

	nd::matrix<T, false> mat_chunk(new_attr, this->data, 0, this->size(), true);

	return mat_chunk;
}

template<typename T, bool ref_holder>
void nd::_matrix<T, ref_holder>::_m_reshape(shape_t shape) {

	coords new_attr = coords(shape);

	if (new_attr.size1d != this->size()) {

		throw nd::exception("nd::matrix<T>::_m_reshape(...), Invalid shape");

	}

	this->attr = new_attr;
}

// ...
template<typename RT, typename T1, typename T2, bool rf_h>
nd::matrix<RT, true> nd::apply_along_axis(const nd::matrix<T1, rf_h> &mat,
		std::function<
				void(T2&, vec1d<max_size_t>&, vec1d<T1>&, max_size_t,
						max_size_t)> func, max_size_t axis, T2 initial_acc,
		std::function<RT(T2)> ppfunc) {

	constexpr max_size_t AUX_VEC_SIZE = 2048;

	nd::matrix<T1, false> tmp = mat;

	if (axis >= tmp.ndim()) {
		throw nd::exception("nd::matrix<T> - axis, Out of Range");
	}

	coords attr = tmp._m_coords();

	coords tmp_attr = attr.swapaxes(0, axis, false);

	coords new_attr = attr.reduce(axis);

	nd::matrix<RT> result(new_attr.shape);

	RandomAccessNdIterator rndIter(tmp_attr);

	max_size_t dim_size = attr.shape[axis];
	big_size_t out_size = tmp.size() / dim_size;

	max_size_t aux_size = std::min(dim_size, AUX_VEC_SIZE);

	max_size_t vi;
	big_size_t index = 0;

	vec1d<T1> elems(aux_size);
	vec1d<max_size_t> indices(aux_size);

	T1 *d0 = tmp._m_begin();
	RT *d1 = result._m_begin();

	T2 acc;

	for (big_size_t i = 0; i < out_size; i++) {

		vi = 0;
		acc = initial_acc;

		for (max_size_t j = 0; j < dim_size; j++) {

			elems[vi] = d0[rndIter.index_at(index++)];
			indices[vi] = j;

			vi++;

			if (vi >= aux_size) {
				vi = 0;
				func(acc, indices, elems, 0, aux_size);
			}
		}

		if (aux_size < dim_size) {

			max_size_t remainder = dim_size % aux_size;

			func(acc, indices, elems, 0, remainder);
		}

		d1[i] = ppfunc(acc);
	}

	return result;
}
