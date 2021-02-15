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

#include "../iterators/RandomAccessNdIterator.hpp"

namespace nd {

template<typename T>
using composite = vec1d<T>;

template<typename T, bool shared_ref = true>
class matrix {

private:

	using data_t = typename ref_t<shared_ref, T>::type;

	template<typename U = T, bool rt = shared_ref>
	using rf = typename matrix<U, rt>::data_t;

	coords attr;

	const_iterator<rf<>> begin();
	const_iterator<rf<>> end();

	matrix<T, false> chunk_at(const coords &attr, big_size_t begin,
			big_size_t end);

//	void movedata(big_size_t begin, big_size_t end);

public:

	vec1d<data_t> data;

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

	coords _m_coords() const;

	matrix<T> copy();

	matrix<T, false> permute(shape_t axes);

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
