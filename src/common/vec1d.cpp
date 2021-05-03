/*
 * vec1d.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./vec1d.hpp"

template<typename T>
vec1d<T>::vec1d() {

}

template<typename T>
vec1d<T>::vec1d(big_size_t size) {

	this->values.resize(size);
}

template<typename T>
vec1d<T>::vec1d(big_size_t size, T val) {

	this->values.resize(size);
	std::fill(this->values.begin(), this->values.end(), val);
}

template<typename T>
vec1d<T>::vec1d(const std::vector<T> &std_vec) :
		values(std_vec) {
}

template<typename T>
vec1d<T>::vec1d(const std::initializer_list<T> &std_init_list) :
		values(std_init_list) {
}

template<typename T>
vec1d<T>::vec1d(const_iterator<T> begin, const_iterator<T> end) {

	this->values.assign(begin, end);
}

// ====================================================================

template<typename T>
big_size_t vec1d<T>::size() const {
	return this->values.size();
}

template<typename T>
void vec1d<T>::reserve(big_size_t size) {
	this->values.reserve(size);
}

template<typename T>
void vec1d<T>::resize(big_size_t size) {
	this->values.resize(size);
}

template<typename T>
void vec1d<T>::push_back(T val) {
	this->values.push_back(val);
}

template<typename T>
void vec1d<T>::pop_back() {
	this->values.pop_back();
}

template<typename T>
void vec1d<T>::assign(const_iterator<T> beign, const_iterator<T> end) {
	this->values.assign(beign, end);
}

template<typename T>
const_iterator<T> vec1d<T>::begin() {
	return this->values.begin();
}

template<typename T>
const_iterator<T> vec1d<T>::end() {
	return this->values.end();
}

template<typename T>
void vec1d<T>::fill(big_size_t size, T val) {

	this->values.resize(size);

	std::fill(this->values.begin(), this->values.end(), val);
}

template<typename T>
void vec1d<T>::range(T start, T end, T step) {

	if (step == 0) {
		throw nd::exception("invalid range, step == 0");
	}

	else if (start >= end) {
		throw nd::exception("invalid range, start >= end");
	}

	big_size_t size = (end - start) / step;

	this->values.resize(size);

	T cur = start;

	for (big_size_t i = 0; i < size; i++) {

		this->values[i] = cur;

		cur += step;
	}
}

template<typename T>
T& vec1d<T>::operator [](big_size_t index) {

	if (index >= this->values.size()) {
		throw nd::exception("Index Out Of Range");
	}

	return this->values[index];
}

template<typename T>
T& vec1d<T>::operator ()(big_size_t index, big_size_t step) {

	if (index * step >= this->values.size()) {
		throw nd::exception("Index Out Of Range");
	}

	return this->values[index * step];
}

// vec1d = std::vector<T>
template<typename T>
vec1d<T> vec1d<T>::operator =(const std::vector<T> &vec) {

	this->values.assign(vec.begin(), vec.end());

	return (*this);
}

// vec1d = {1, 2, 3, ...etc} ---> std::initializer_list<T>
template<typename T>
vec1d<T> vec1d<T>::operator =(const std::initializer_list<T> &std_init_list) {

	this->values.assign(std_init_list.begin(), std_init_list.end());

	return (*this);
}

// vec1d = vec1d
template<typename T>
vec1d<T> vec1d<T>::operator =(const vec1d<T> &vec) {

	this->values.assign(vec.values.begin(), vec.values.end());

	return (*this);
}

// vec1d == vec1d
template<typename T>
bool vec1d<T>::operator ==(const vec1d<T> &vec) {

	vec1d<T> temp = vec;

	if (this->size() != temp.size()) {
		throw nd::exception("Invalid boolean operation, "
				"vectors must have the same shape");
	}

	for (big_size_t i = 0; i < temp.size(); i++) {

		if (this->operator [](i) != temp[i]) {
			return false;
		}
	}

	return true;
}

// vec1d != vec1d
template<typename T>
bool vec1d<T>::operator !=(const vec1d<T> &vec) {

	vec1d<T> temp = vec;

	if (this->size() != temp.size()) {
		throw nd::exception("Invalid boolean operation, "
				"vectors must have the same shape");
	}

	for (big_size_t i = 0; i < temp.size(); i++) {
		if (this->operator [](i) != temp[i]) {
			return true;
		}
	}

	return false;
}

// vec1d[i] == (int | long long | ... etc), returns a boolean vector (mask)
template<typename T>
vec1d<bool> vec1d<T>::operator ==(const T &val) {

	vec1d<bool> mask_vec(this->size());

	for (big_size_t i = 0; i < this->size(); i++) {
		mask_vec[i] = (this->operator [](i) == val);
	}

	return mask_vec;
}

// ====================================================================

// vec1d + vec1d
template<typename T>
vec1d<T> vec1d<T>::operator +(const vec1d<T> &vec) {

	vec1d<T> temp = vec;

	if (this->size() != temp.size()) {
		throw nd::exception("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	vec1d<T> res_vec(*this);

	for (big_size_t i = 0; i < temp.size(); i++) {
		res_vec[i] += temp[i];
	}

	return res_vec;
}

// vec1d += vec1d

template<typename T>
vec1d<T>& vec1d<T>::operator +=(const vec1d<T> &vec) {

	vec1d<T> temp = vec;

	if (this->size() != temp.size()) {
		throw nd::exception("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	for (big_size_t i = 0; i < temp.size(); i++) {
		this->operator [](i) += temp[i];
	}

	return (*this);
}

// vec1d + (int | long long | ...etc)
template<typename T>
vec1d<T> vec1d<T>::operator +(const T &val) {

	vec1d<T> res_vec(*this);

	for (big_size_t i = 0; i < res_vec.size(); i++) {
		res_vec[i] += val;
	}

	return res_vec;
}

// vec1d += (int | long long | ...etc)
template<typename T>
vec1d<T>& vec1d<T>::operator +=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		this->operator[](i) += val;
	}

	return (*this);
}

// ====================================================================

// vec1d - vec1d

template<typename T>
vec1d<T> vec1d<T>::operator -(const vec1d<T> &vec) {

	vec1d<T> temp = vec;

	if (this->size() != temp.size()) {
		throw nd::exception("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	vec1d<T> res_vec(*this);

	for (big_size_t i = 0; i < temp.size(); i++) {
		res_vec[i] -= temp[i];
	}

	return res_vec;
}

// vec1d -= vec1d

template<typename T>
vec1d<T>& vec1d<T>::operator -=(const vec1d<T> &vec) {

	vec1d<T> temp = vec;

	if (this->size() != temp.size()) {
		throw nd::exception("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	for (big_size_t i = 0; i < temp.size(); i++) {
		this->operator [](i) -= temp[i];
	}

	return (*this);
}

// vec1d - (int | long long | ...etc)
template<typename T>
vec1d<T> vec1d<T>::operator -(const T &val) {

	vec1d<T> res_vec(*this);

	for (big_size_t i = 0; i < res_vec.size(); i++) {
		res_vec[i] -= val;
	}

	return res_vec;
}

// vec1d -= (int | long long | ...etc)
template<typename T>
vec1d<T>& vec1d<T>::operator -=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		this->operator [](i) -= val;
	}

	return (*this);
}

// ====================================================================

// vec1d * vec1d

template<typename T>
vec1d<T> vec1d<T>::operator *(const vec1d<T> &vec) {

	vec1d<T> temp = vec;

	if (this->size() != temp.size()) {
		throw nd::exception("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	vec1d<T> res_vec(*this);

	for (big_size_t i = 0; i < temp.size(); i++) {
		res_vec[i] *= temp[i];
	}

	return res_vec;
}

// vec1d *= vec1d

template<typename T>
vec1d<T>& vec1d<T>::operator *=(const vec1d<T> &vec) {

	vec1d<T> temp = vec;

	if (this->size() != temp.size()) {
		throw nd::exception("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	for (big_size_t i = 0; i < temp.size(); i++) {
		this->operator [](i) *= temp[i];
	}

	return (*this);
}

// vec1d * (int | long long | ...etc)
template<typename T>
vec1d<T> vec1d<T>::operator *(const T &val) {

	vec1d<T> res_vec(*this);

	for (big_size_t i = 0; i < res_vec.size(); i++) {
		res_vec[i] *= val;
	}

	return res_vec;
}

// vec1d *= (int | long long | ...etc)
template<typename T>
vec1d<T>& vec1d<T>::operator *=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		this->operator [](i) *= val;
	}

	return (*this);
}

// ====================================================================

// vec1d / (int | long long | ...etc)
template<typename T>
vec1d<T> vec1d<T>::operator /(const T &val) {

	vec1d<T> res_vec(*this);

	for (big_size_t i = 0; i < res_vec.size(); i++) {
		res_vec[i] /= val;
	}

	return res_vec;
}

// vec1d /= (int | long long | ...etc)
template<typename T>
vec1d<T>& vec1d<T>::operator /=(const T &val) {

	for (big_size_t i = 0; i < this->size(); i++) {
		this->operator ()[i] /= val;
	}

	return (*this);
}

// ====================================================================

/*
 * Apply custom void function, function parameter T vec1d[i]
 * function overwrite vector values, therefore value must be passed
 * by reference apply function on a specific, range of vector values.
 */
template<typename T>
void vec1d<T>::write_in_range(big_size_t begin, big_size_t end,
		std::function<void(T &vec_i)> custom_func) {

	for (big_size_t i = begin; i < end; i++) {
		custom_func(this->operator [](i));
	}
}

/*
 * Apply custom function with return type T, apply function
 * on a specific range of vector values.
 */
template<typename T>
void vec1d<T>::apply_in_range(big_size_t begin, big_size_t end,
		std::function<T(T vec_i)> custom_func) {

	for (big_size_t i = begin; i < end; i++) {
		this->operator [](i) = custom_func(this->operator [](i));
	}
}

/* Sum values in a specific range of the vector.
 *
 * algorithm.h - : (0, 1, 2, 3) -
 *-----------------------------
 * 0. Naive summation
 * 1. Pairwise summation (default)
 * 2. Kahan summation
 * 3. Shift reduce sum
 */
template<typename T>
T vec1d<T>::sum(big_size_t begin, big_size_t end) {
	return algorithm::_h::pairwise_summation<T>(begin, end, &(this->values[0]));
}

template<typename T>
T vec1d<T>::multiply(big_size_t begin, big_size_t end) {

	T result = 1;

	for (big_size_t i = begin; i < end; i++) {
		result *= this->operator [](i);
	}

	return result;
}

template<typename T>
void vec1d<T>::print_vec1d(big_size_t begin, big_size_t end) {

	std::cout << "[";

	for (big_size_t i = begin; i < end - 1; i++) {
		std::cout << this->operator [](i) << ", ";
	}

	std::cout << this->operator [](end - 1) << "]";

}

template<typename T>
vec1d<T>::~vec1d() {

}

template<typename T>
vec1d<T>::vec1d(const vec1d<T> &&vec) noexcept :
		values(std::move(vec.values)) {
}

template<typename T>
vec1d<T>::vec1d(const vec1d<T> &vec) noexcept {

	this->values.assign(vec.values.begin(), vec.values.end());
}

std::ostream& operator <<(std::ostream &os, shape_t shape) {

	os << '(';

	for (max_size_t i = 0; i < shape.size() - 1; i++) {
		os << shape[i] << ',';
	}

	os << shape[shape.size() - 1];

	if (shape.size() == 1) {
		os << ',';
	}

	os << ')';

	return os;
}

// flags: {0: doesn't match, 1: match, 2: broadcastable}
uflag8_t operator &(const shape_t &shape1, const shape_t &shape2) {

	shape_t temp1 = shape1;
	shape_t temp2 = shape2;

	max_size_t size1 = temp1.size();
	max_size_t size2 = temp2.size();

	uflag8_t flag = 1;

	if (size1 == size2) {
		for (max_size_t i = 0; i < size1; i++) {
			if (temp1[i] != temp2[i]) {

				if (temp1[i] == 1 || temp2[i] == 1) {

					flag = 2;
				}

				else {
					return 0;
				}
			}
		}
		return flag;
	}

	else {

		max_size_t i, j;

		if (size1 > size2) {
			i = size1 - size2;
			j = 0;
		}

		else {
			i = 0;
			j = size2 - size1;
		}

		while (i < size1 && j < size2) {

			if ((temp1[i] != temp2[j]) && !(temp1[i] == 1 || temp2[j] == 1)) {
				return 0;
			}

			i++;
			j++;
		}

		return 2;
	}
}

