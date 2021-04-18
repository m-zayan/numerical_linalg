/*
 * _matrix.hpp
 *
 *	Author: Z. Mohamed
 *
 *	linear storage (1D), _matrix.
 */

#ifndef SRC_MULTIDIM_MATRIX_HPP
#define SRC_MULTIDIM_MATRIX_HPP

#include "ufunc.hpp"

// nd
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

	bool req_iter;

	template<typename RT, bool ref_h = ref_holder>
	matrix<RT, ref_h>* _m_dynamic_cast();

public:

	inline big_size_t size();

	inline shape_t shape();
	inline shape_t strides();

	inline max_size_t ndim();

	inline max_size_t step_size();

	inline bool own_data();

	// ===================
	matrix<T, false> operator [](max_size_t d_index);

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

	void assign(shape_t indices, T val);

	T& at(shape_t indices);

	matrix<T> copy();

	// ===================

	T* _m_begin();
	T* _m_end();

	coords _m_coords() const;
	data_t _m_ptr() const;

	vec1d<T> _m_data() const;

	big_size_t _m_c_begin() const;
	big_size_t _m_c_end() const;

	bool _m_req_iter() const;

	// ===================

	matrix<T, false> permute(shape_t axes);

	matrix<T, false> reshape(shape_t shape);

	void _m_reshape(shape_t shape);

	virtual ~_matrix();

};

template<typename T, bool ref_holder>
class matrix: public _matrix<T, ref_holder> {
};

// matrix<T, true>
template<typename T>
class matrix<T, true> : public _matrix<T, true> {

public:

	matrix() = delete;

	matrix(shape_t shape);
	matrix(shape_t shape, T val);
	matrix(const coords &attr);

	matrix(const matrix<T> &mat);
	matrix(const matrix<T, false> &mat);

	~matrix();

};

// matrix<T, false>
template<typename T>
class matrix<T, false> : public _matrix<T, false> {

public:

	matrix() = delete;

	matrix(const coords &attr, shared_ptr<vec1d<T>> data, big_size_t c_begin,
			big_size_t c_end, bool req_iter);

	matrix(const coords &attr, weak_ptr<vec1d<T>> data, big_size_t c_begin,
			big_size_t c_end, bool req_iter);

	matrix(const matrix &mat);
	matrix(const matrix<T, true> &mat);

	~matrix();
};

// end matrix class

// ufunc

template<typename T>
matrix<T> stack(composite<matrix<T>> matrix_list);

/*
 * 	n_splits = dim_size / AUX_VEC_SIZE
 * 	func(acaccumulator, indices, values, _, _)
 */
template<typename RT, typename T1, typename T2, bool rf_h>
matrix<RT, true> apply_along_axis(const matrix<T1, rf_h> &mat,
		std::function<
				void(T2&, vec1d<max_size_t>&, vec1d<T1>&, max_size_t,
						max_size_t)> func, max_size_t axis, T2 initial_acc,
		std::function<RT(T2)> ppfunc);

namespace random {

template<typename T>
matrix<T> uniform(T low, T high, shape_t shape);

}

namespace numeric {

template<typename RT, typename T, bool rf_h>
matrix<RT, true> min(const matrix<T, rf_h> &mat, max_size_t axis);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> max(const matrix<T, rf_h> &mat, max_size_t axis);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> argmax(const matrix<T, rf_h> &mat, max_size_t axis);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> argmin(const matrix<T, rf_h> &mat, max_size_t axis);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> sum(const matrix<T, rf_h> &mat, max_size_t axis);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> mean(const matrix<T, rf_h> &mat, max_size_t axis);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> var(const matrix<T, rf_h> &mat, max_size_t axis);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> std(const matrix<T, rf_h> &mat, max_size_t axis);

template<typename RT, typename T, bool rf_h>
matrix<RT, true> mod(const matrix<T, rf_h> &mat, max_size_t axis);

template<typename RT, typename T, bool rf_h, typename qT>
matrix<RT, true> quantile(const matrix<T, rf_h> &mat, qT q, max_size_t axis);

}

}

#endif /* SRC_MULTIDIM_MATRIX_HPP */
