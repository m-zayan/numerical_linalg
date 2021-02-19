/*
 * _matrix.hpp
 *
 *	Author: Z. Mohamed
 *
 *	linear storage (1D), _matrix.
 */

#ifndef SRC_MULTIDIM_MATRIX_HPP
#define SRC_MULTIDIM_MATRIX_HPP

#include <algorithm>

#include "../iterators/RandomAccessNdIterator.hpp"

// type
namespace _t {

template<typename T, bool ref_holder> struct dt;

template<typename T> struct dt<T, true> {

	using type = shared_ptr<vec1d<T>>;
};

template<typename T> struct dt<T, false> {

	using type = weak_ptr<vec1d<T>>;

};

}

// nd
namespace nd {

template<typename T, bool ref_holder = true>
class matrix;

template<typename T>
using composite = vec1d<T>;

// functions

template<typename T>
matrix<T> stack(composite<matrix<T>> matrix_list);

namespace random {

template<typename T>
matrix<T> uniform(T low, T high, shape_t shape);

}

// end functions

template<typename T, bool ref_holder>
class _matrix {

protected:

	using data_t = typename _t::dt<T, ref_holder>::type;
	using mat_t = matrix<T, ref_holder>;

	coords attr;

	big_size_t c_begin;
	big_size_t c_end;

	template<typename RT, bool ref_h = ref_holder>
	matrix<RT, ref_h>* _m_dynamic_cast();

	matrix<T> reordered_chunk(bool use_iter);

public:

	data_t data;

	matrix<T, false> operator [](max_size_t d_index);

	template<bool ref_h>
	matrix<T, false>& operator =(const matrix<T, ref_h> &mat);

	inline big_size_t size();

	inline shape_t shape();
	inline shape_t strides();

	inline max_size_t ndim();

	inline max_size_t step_size();

	inline bool own_data();

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

	//	 mask - (min_size_t -> should be modified -> mask object)
	matrix<min_size_t> operator ==(const T &val);

	matrix<T> operator +(const T &val);
	mat_t& operator +=(const T &val);

	matrix<T> operator -(const T &val);
	mat_t& operator -=(const T &val);

	matrix<T> operator *(const T &val);
	mat_t& operator *=(const T &val);

	matrix<T> operator /(const T &val);

	mat_t& operator /=(const T &val);

	void assign(shape_t indices, T val);

	// ===================

	template<typename U, typename RT>
	void _m_data_wrapper(U *d0, RT *d1, big_size_t s1, big_size_t c_begin,
			big_size_t c_end, std::function<void(U&, RT&)> func);

	void _m_write_in_range(big_size_t c_begin, big_size_t c_end,
			std::function<void(T&)> func);

	T* _m_begin();
	T* _m_end();

	coords _m_coords() const;
	data_t _m_ptr() const;

	vec1d<T> _m_data() const;

	big_size_t _m_c_begin() const;
	big_size_t _m_c_end() const;

	// ===================

	matrix<T, false> permute(shape_t axes);

	virtual ~_matrix();

	template<typename U>
	friend matrix<U> random::uniform(U low, U high, shape_t shape);

	template<typename U>
	friend matrix<U> stack(composite<matrix<U>> matrix_list);
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

	matrix<T> copy();

	matrix(const matrix &mat) = default;
	matrix(const matrix<T, false> &mat);

	~matrix();

};

// matrix<T, false>
template<typename T>
class matrix<T, false> : public _matrix<T, false> {

public:

	matrix() = delete;

	matrix(const coords &attr, shared_ptr<vec1d<T>> data, big_size_t c_begin,
			big_size_t c_end);

	matrix(const coords &attr, weak_ptr<vec1d<T>> data, big_size_t c_begin,
			big_size_t c_end);

	matrix<T> copy();

	matrix(const matrix &mat) = default;
	matrix(const matrix<T, true> &mat);

	~matrix();
};

// end matrix class
}

// end nd

#endif /* SRC_MULTIDIM_MATRIX_HPP */
