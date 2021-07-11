/*
 * _matrix.hpp
 *
 *	Author: Z. Mohamed
 *
 *	linear storage (1D), _matrix.
 */

#ifndef SRC_MULTIDIM_MATRIX_HPP
#define SRC_MULTIDIM_MATRIX_HPP

#include "./ufunc.hpp"

namespace nd {

template<typename T, bool ref_holder = true>
class matrix;

template<typename T>
using composite = vec1d<T>;

template<typename T, bool ref_holder>
class _matrix {

protected:

	using data_t = _type::data_t<T, ref_holder>;
	using mat_t = matrix<T, ref_holder>;

	coords attr;
	data_t data;

	big_size_t c_begin;
	big_size_t c_end;

	template<typename RT, bool ref_h = ref_holder>
	matrix<RT, ref_h>* _m_dynamic_cast();

public:

	static uflag8_t _m_validate_op(const coords &attr0, const coords &attr1);

	static nd::matrix<T> _m_alloc_if_broadcastable(coords &attr0,
			coords &attr1);

	static nd::matrix<T> _m_alloc_if_broadcastable(coords &attr0, coords &attr1,
			T val);

	// ===========================================================================

	big_size_t size() const;

	shape_t shape() const;
	strides_t strides() const;

	max_size_t ndim() const;

	max_size_t step_size() const;

	bool own_data() const;

	// ===========================================================================

	matrix<T, false> operator [](max_size_t d_index);

	// ===========================================================================

	// _matrix <---> _matrix
	template<bool ref_h>
	bool operator ==(const matrix<T, ref_h> &mat);

	template<bool ref_h>
	matrix<T> operator +(const matrix<T, ref_h> &mat);

	template<bool ref_h>
	mat_t& operator +=(const matrix<T, ref_h> &mat);

	template<bool ref_h>
	matrix<T> operator -(const matrix<T, ref_h> &mat);

	template<bool ref_h>
	mat_t& operator -=(const matrix<T, ref_h> &mat);

	template<bool ref_h>
	matrix<T> operator *(const matrix<T, ref_h> &mat);

	template<bool ref_h>
	mat_t& operator *=(const matrix<T, ref_h> &mat);

	// ===========================================================================

	// _matrix <---> value
	matrix<mask_t> operator ==(const T &val);

	matrix<T> operator +(const T &val);
	mat_t& operator +=(const T &val);

	matrix<T> operator -(const T &val);
	mat_t& operator -=(const T &val);

	matrix<T> operator *(const T &val);
	mat_t& operator *=(const T &val);

	matrix<T> operator /(const T &val);

	mat_t& operator /=(const T &val);

	mat_t& operator =(const T &val);

	void assign(shape_t indices, T val);

	T& at(shape_t indices);

	matrix<T> copy();

	template<typename RT>
	operator matrix<RT>() const;

	template<typename RT>
	explicit operator RT() const;

	// ===========================================================================

	vec1d<T> _m_data() const;

	coords _m_coords() const;
	data_t _m_ptr() const;

	big_size_t _m_c_begin() const;
	big_size_t _m_c_end() const;

	T* _m_begin();
	T* _m_end();

	IteratorType _m_iter_type() const;

	// ===========================================================================

	matrix<T, false> permute(shape_t axes) const;

	matrix<T, false> reshape(shape_t shape) const;

	matrix<T, false> set_new_coords(const coords &attr) const;

	matrix<T, false> op_view_2d() const;

	// ===========================================================================

	void _m_reshape(shape_t shape);
	void _m_clear_iter_type();

	// ===========================================================================

	virtual ~_matrix();

};

template<typename T, bool ref_holder>
class matrix: public _matrix<T, ref_holder> {
};

// matrix<T, true>
template<typename T>
class matrix<T, true> : public _matrix<T, true> {

public:

	using _matrix<T, true>::operator=;

	matrix() = delete;

	matrix(shape_t shape);
	matrix(shape_t shape, T val);

	matrix(const coords &attr, T val);
	matrix(const coords &attr);

	matrix(const matrix<T> &mat);
	matrix(const matrix<T, false> &mat);

	~matrix();

};

// matrix<T, false>
template<typename T>
class matrix<T, false> : public _matrix<T, false> {

public:

	using _matrix<T, false>::operator=;

	matrix() = delete;

	matrix(const coords &attr, shared_ptr<vec1d<T>> data, big_size_t c_begin,
			big_size_t c_end);

	matrix(const coords &attr, weak_ptr<vec1d<T>> data, big_size_t c_begin,
			big_size_t c_end);

	matrix(const matrix &mat);
	matrix(const matrix<T, true> &mat);

	~matrix();
};

/* ##################################################################################### */

template<typename T>
matrix<T> stack(composite<matrix<T, false>> matrix_list);

/* ##################################################################################### */

namespace random {

template<typename T>
matrix<T> uniform(T low, T high, shape_t shape);

}

/* ##################################################################################### */

template<typename RT, typename T, bool rf_h>
matrix<RT> apply(const matrix<T, rf_h> &mat, std::function<RT(T)> func);

/*
 * 	n_splits = dim_size / AUX_VEC_SIZE
 * 	func(acaccumulator, indices, values, _, _)
 */
template<typename RT, typename T1, typename T2, bool rf_h>
matrix<RT> apply_along_axis(const matrix<T1, rf_h> &mat,
		std::function<
				void(T2&, vec1d<max_size_t>&, vec1d<T1>&, max_size_t,
						max_size_t)> func, max_size_t axis, T2 initial_acc,
		std::function<RT(T2&)> ppfunc, bool reduce, bool keepdims);

/* ##################################################################################### */

namespace numeric {

template<typename RT, typename T, bool rf_h>
matrix<RT, true> min(const matrix<T, rf_h> &mat, max_size_t axis,
		bool keepdims = false);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> max(const matrix<T, rf_h> &mat, max_size_t axis,
		bool keepdims = false);

template<typename RT = max_size_t, typename T, bool rf_h>
matrix<RT, true> argmax(const matrix<T, rf_h> &mat, max_size_t axis,
		bool keepdims = false);

template<typename RT = max_size_t, typename T, bool rf_h>
matrix<RT, true> argmin(const matrix<T, rf_h> &mat, max_size_t axis,
		bool keepdims = false);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> sum(const matrix<T, rf_h> &mat, max_size_t axis,
		bool keepdims = false);

template<typename RT = float_auto, typename T, bool rf_h>
matrix<RT, true> mean(const matrix<T, rf_h> &mat, max_size_t axis,
		bool keepdims = false);

template<typename RT = float_auto, typename T, bool rf_h>
matrix<RT, true> var(const matrix<T, rf_h> &mat, max_size_t axis,
		bool keepdims = false);

template<typename RT = float_auto, typename T, bool rf_h>
matrix<RT, true> std(const matrix<T, rf_h> &mat, max_size_t axis,
		bool keepdims = false);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> mod(const matrix<T, rf_h> &mat, max_size_t axis,
		bool keepdims = false);

template<typename RT = float_auto, typename T, bool rf_h,
		typename qT = float_auto>
matrix<RT, true> quantile(const matrix<T, rf_h> &mat, qT q, max_size_t axis,
		bool keepdims = false);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> cumsum(const matrix<T, rf_h> &mat, max_size_t axis);

}

/* ##################################################################################### */

}

#endif /* SRC_MULTIDIM_MATRIX_HPP */
