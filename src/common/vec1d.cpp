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

	vec1d<T> temp = std::move(vec);

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

	vec1d<T> temp = std::move(vec);

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

	vec1d<T> temp = std::move(vec);

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

	vec1d<T> temp = std::move(vec);

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

	vec1d<T> temp = std::move(vec);

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

	vec1d<T> temp = std::move(vec);

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

	vec1d<T> temp = std::move(vec);

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

	vec1d<T> temp = std::move(vec);

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
	return algorithm<T>::pairwise_summation(begin, end, this->values);
}

template<typename T>
T vec1d<T>::multiply(big_size_t begin, big_size_t end) {

	big_size_t result = 1;

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
void vec1d<T>::rprint_vec1d(big_size_t begin, big_size_t end) {

	std::cout << "[";

	for (big_size_t i = begin; i < end - 1; i++) {
		std::cout << *this->operator [](i).get() << ", ";
	}

	std::cout << *this->operator [](end - 1).get() << "]";

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

	if (shape.size() > 1) {
		os << shape[shape.size() - 1] << ')';
	} else {
		os << shape[shape.size() - 1] << ", " << 1 << ')';
	}
	return os;
}
