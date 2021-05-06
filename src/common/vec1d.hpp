/*
 * vec1d.hpp
 *
 *	Author: Z. Mohamed
 *
 *	 vector-1d,
 *
 *	 Arithmetical operations are explicit
 *	 (i.e. conversions are not allowed - vec1d<float> + vec1d<int>)
 */

#ifndef SRC_VEC1D_HPP
#define SRC_VEC1D_HPP

#include "./typing/gtypes/types.hpp"

template<typename T>
class vec1d {

protected:

	std::vector<T> values;

public:

	vec1d();
	vec1d(big_size_t size);
	vec1d(big_size_t size, T val);
	vec1d(const std::vector<T> &std_vec);
	vec1d(const std::initializer_list<T> &std_init_list);
	vec1d(const_iterator<T> begin, const_iterator<T> end);

	big_size_t size() const;

	T* ref(big_size_t index);

	void reserve(big_size_t size);
	void resize(big_size_t size);

	void push_back(T val);
	void pop_back();
	void assign(const_iterator<T> begin, const_iterator<T> end);
	void fill(big_size_t size, T val);
	void range(T start, T end, T step);

	const_iterator<T> begin();
	const_iterator<T> end();

	T& operator [](big_size_t index);
	T& operator ()(big_size_t index, big_size_t step);

	// vec1d = vec1d
	vec1d<T> operator =(const vec1d<T> &vec);

	// vec1d = std::vector<T>
	vec1d<T> operator =(const std::vector<T> &vec);

	// vec1d = {1, 2, 3, ...etc} ---> std::initializer_list<T>
	vec1d<T> operator =(const std::initializer_list<T> &std_init_list);

	// vector <---> vector
	bool operator ==(const vec1d<T> &vec);
	bool operator !=(const vec1d<T> &vec);

	vec1d<T> operator +(const vec1d<T> &vec);
	vec1d<T>& operator +=(const vec1d<T> &vec);

	vec1d<T> operator -(const vec1d<T> &vec);
	vec1d<T>& operator -=(const vec1d<T> &vec);

	vec1d<T> operator *(const vec1d<T> &vec);
	vec1d<T>& operator *=(const vec1d<T> &vec);

	// vector <---> value
	vec1d<bool> operator ==(const T &val);

	vec1d<T> operator +(const T &val);
	vec1d<T>& operator +=(const T &val);

	vec1d<T> operator -(const T &val);
	vec1d<T>& operator -=(const T &val);

	vec1d<T> operator *(const T &val);
	vec1d<T>& operator *=(const T &val);

	vec1d<T> operator /(const T &val);
	vec1d<T>& operator /=(const T &val);

	/*
	 * Apply custom void function, function parameter T vec1d[i]
	 * function overwrite vector values, therefore value must be passed
	 * by reference, apply function on a specific, range of vector values.
	 */
	void write_in_range(big_size_t begin, big_size_t end,
			std::function<void(T &vec_i)> custom_func);

	/*
	 * Apply custom function with return type T, apply function
	 * over a specific range of vector values.
	 */
	void apply_in_range(big_size_t begin, big_size_t end,
			std::function<T(T vec_i)> custom_func);

	/* Sum values in a specific range of the vector.
	 * 	### Naive summation,
	 *
	 * 		check: [./common/algorithm.hpp]
	 */
	T sum(big_size_t begin, big_size_t end);

	T multiply(big_size_t begin, big_size_t end);

	void print_vec1d(big_size_t begin, big_size_t end);

	virtual ~vec1d();

	vec1d(const vec1d<T> &vec) noexcept;
	vec1d(const vec1d<T> &&vec) noexcept;

};

#endif /* SRC_VEC1D_HPP */
