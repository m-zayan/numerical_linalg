/*
 * matrix.hpp
 *
 *	Author: Z. Mohamed
 *
 *	linear storage (1D), matrix.
 */

#ifndef SRC_MULTIDIM_MATRIX_HPP
#define SRC_MULTIDIM_MATRIX_HPP

#include <algorithm>

#include "../shapes/coords.hpp"

namespace nd {

template<typename T>
using composite = vec1d<T>;

template<typename T, bool shared_ref = true>
class matrix {

private:

	template<typename U = T>
	using data_t = typename ref_t<shared_ref, U>::type;

	coords attr;

	const_iterator<data_t<T>> begin();
	const_iterator<data_t<T>> end();

	matrix<T, false> chunk_at(const coords &attr, big_size_t begin,
			big_size_t end);

public:

	vec1d<data_t<T>> data;

	matrix() = delete;

	matrix(shape_t shape);
	matrix(shape_t shape, T val);
	matrix(const coords &&attr);

	matrix<T, false> operator [](max_size_t d_index);
	matrix<T, false>& operator =(const matrix<T> &mat);

	inline big_size_t size();

	inline shape_t shape();
	inline shape_t strides();

	inline max_size_t ndim();

	inline max_size_t step_size();

	inline bool own_data();

	// matrix <---> matrix
	bool operator ==(const matrix<T> &mat);

	matrix<T> operator +(const matrix<T> &mat);
	matrix<T>& operator +=(const matrix<T> &mat);

	matrix<T> operator -(const matrix<T> &mat);
	matrix<T>& operator -=(const matrix<T> &mat);

	matrix<T> operator *(const matrix<T> &mat);
	matrix<T>& operator *=(const matrix<T> &mat);

	// matrix <---> value
	matrix<bool> operator ==(const T &val);

	matrix<T> operator +(const T &val);
	matrix<T>& operator +=(const T &val);

	matrix<T> operator -(const T &val);
	matrix<T>& operator -=(const T &val);

	matrix<T> operator *(const T &val);
	matrix<T>& operator *=(const T &val);

	matrix<T> operator /(const T &val);
	matrix<T>& operator /=(const T &val);

	void assign(shape_t indices, T val);
	void print_matrix();

	big_size_t index_at(shape_t indices);

	coords _m_attr() const;
	void _prem(shape_t axes);

	matrix<T> copy();

	matrix(const matrix &mat) noexcept;
	matrix(const matrix &&mat) noexcept;

	virtual ~matrix();

};

template<typename T>
matrix<T> stack(composite<matrix<T>> matrix_list);

}

namespace nd::random {

template<typename T>
matrix<T> uniform(T low, T high, shape_t shape);

}

#endif /* SRC_MULTIDIM_MATRIX_HPP */
