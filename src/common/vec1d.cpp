/*
 * vec1d.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./vec1d.hpp"

template<typename T>
vec1d<T>::vec1d() :
		values( { }) {

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
template<typename RT>
std::vector<RT> vec1d<T>::as_std_vec() const {

	std::vector<RT> std_vec(this->size());

	for (big_size_t i = 0; i < this->size(); i++) {

		std_vec[i] = static_cast<RT>(this->operator [](i));
	}

	return std_vec;
}

template<typename T>
template<typename RT>
vec1d<T>::operator vec1d<RT>() const {

	vec1d<RT> res_vec(this->size());

	for (big_size_t i = 0; i < this->size(); i++) {

		res_vec[i] = static_cast<RT>(this->operator [](i));
	}

	return res_vec;
}

// ====================================================================

template<typename T>
T* vec1d<T>::ref(big_size_t index) {
	return &(this->values[index]);
}

template<typename T>
bool vec1d<T>::contains_scalar() const {
	return std::is_scalar<T>::value;
}

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
void vec1d<T>::push_back(const T& val) {
	this->values.push_back(val);
}

template<typename T>
void vec1d<T>::emplace_back(const T& val) {
	this->values.emplace_back(val);
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
void vec1d<T>::fill(T val) {

	std::fill(this->begin(), this->end(), val);
}

template<typename T>
void vec1d<T>::fill(big_size_t size, T val) {

	this->resize(size);

	std::fill(this->begin(), this->end(), val);
}

template<typename T>
void vec1d<T>::range(T start, T end, T step) {

	if (step == 0) {
		throw std::logic_error("Invalid Range, step == 0");
	}

	else if (start >= end) {
		throw std::logic_error("Invalid Range, start >= end");
	}

	big_size_t size = (end - start) / step;

	this->resize(size);

	T cur = start;

	for (big_size_t i = 0; i < size; i++) {

		this->operator [](i) = cur;

		cur += step;
	}
}

template<typename T>
T& vec1d<T>::operator [](big_size_t index) {

	if (index >= this->size()) {
		throw std::logic_error("Index Out Of Range");
	}

	return this->values[index];
}

template<typename T>
const T& vec1d<T>::operator [](big_size_t index) const {

	if (index >= this->size()) {
		throw std::logic_error("Index Out Of Range");
	}

	return this->values[index];
}

template<typename T>
T& vec1d<T>::operator ()(big_size_t index, big_size_t step) {

	if (index * step >= this->size()) {
		throw std::logic_error("Index Out Of Range");
	}

	return this->values[index * step];
}

// vec1d = std::vector<T>
template<typename T>
vec1d<T>& vec1d<T>::operator =(const std::vector<T> &vec) {

	this->values.assign(vec.begin(), vec.end());

	return (*this);
}

// vec1d = {1, 2, 3, ...etc} ---> std::initializer_list<T>
template<typename T>
vec1d<T>& vec1d<T>::operator =(const std::initializer_list<T> &std_init_list) {

	this->values.assign(std_init_list.begin(), std_init_list.end());

	return (*this);
}

// vec1d = vec1d
template<typename T>
vec1d<T>& vec1d<T>::operator =(const vec1d<T> &vec) {

	this->values.assign(vec.values.begin(), vec.values.end());

	return (*this);
}

// vec1d == vec1d
template<typename T>
bool vec1d<T>::operator ==(const vec1d<T> &vec) const {

	if (this->size() != vec.size()) {
		throw std::logic_error("Invalid boolean operation, "
				"vectors must have the same shape");
	}

	for (big_size_t i = 0; i < vec.size(); i++) {

		if (this->operator [](i) != vec[i]) {
			return false;
		}
	}

	return true;
}

// vec1d != vec1d
template<typename T>
bool vec1d<T>::operator !=(const vec1d<T> &vec) const {

	if (this->size() != vec.size()) {
		throw std::logic_error("Invalid boolean operation, "
				"vectors must have the same shape");
	}

	for (big_size_t i = 0; i < vec.size(); i++) {
		if (this->operator [](i) != vec[i]) {
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
vec1d<T> vec1d<T>::operator +(const vec1d<T> &vec) const {

	if (this->size() != vec.size()) {
		throw std::logic_error("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	vec1d<T> res_vec(*this);

	for (big_size_t i = 0; i < vec.size(); i++) {
		res_vec[i] += vec[i];
	}

	return res_vec;
}

// vec1d += vec1d

template<typename T>
vec1d<T>& vec1d<T>::operator +=(const vec1d<T> &vec) {

	if (this->size() != vec.size()) {
		throw std::logic_error("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	for (big_size_t i = 0; i < vec.size(); i++) {
		this->operator [](i) += vec[i];
	}

	return (*this);
}

// vec1d + (int | long long | ...etc)
template<typename T>
vec1d<T> vec1d<T>::operator +(const T &val) const {

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
vec1d<T> vec1d<T>::operator -(const vec1d<T> &vec) const {

	if (this->size() != vec.size()) {
		throw std::logic_error("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	vec1d<T> res_vec(*this);

	for (big_size_t i = 0; i < vec.size(); i++) {
		res_vec[i] -= vec[i];
	}

	return res_vec;
}

// vec1d -= vec1d

template<typename T>
vec1d<T>& vec1d<T>::operator -=(const vec1d<T> &vec) {

	if (this->size() != vec.size()) {
		throw std::logic_error("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	for (big_size_t i = 0; i < vec.size(); i++) {
		this->operator [](i) -= vec[i];
	}

	return (*this);
}

// vec1d - (int | long long | ...etc)
template<typename T>
vec1d<T> vec1d<T>::operator -(const T &val) const {

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
vec1d<T> vec1d<T>::operator *(const vec1d<T> &vec) const {

	if (this->size() != vec.size()) {
		throw std::logic_error("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	vec1d<T> res_vec(*this);

	for (big_size_t i = 0; i < vec.size(); i++) {
		res_vec[i] *= vec[i];
	}

	return res_vec;
}

// vec1d *= vec1d

template<typename T>
vec1d<T>& vec1d<T>::operator *=(const vec1d<T> &vec) {

	if (this->size() != vec.size()) {
		throw std::logic_error("Invalid element-wise operation, "
				"vectors must have the same shape");
	}

	for (big_size_t i = 0; i < vec.size(); i++) {
		this->operator [](i) *= vec[i];
	}

	return (*this);
}

// vec1d * (int | long long | ...etc)
template<typename T>
vec1d<T> vec1d<T>::operator *(const T &val) const {

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
vec1d<T> vec1d<T>::operator /(const T &val) const {

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
		this->operator [](i) /= val;
	}

	return (*this);
}

// ====================================================================

template<typename T>
vec1d<T> vec1d<T>::slice(big_size_t begin, big_size_t end) const {

	if (begin > end || end > this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::slice(...)");
	}

	big_size_t new_size = end - begin;

	vec1d<T> res_vec(new_size);

	for (big_size_t i = begin; i < end; i++) {

		res_vec[i - begin] = this->operator [](i);
	}

	return res_vec;
}

template<typename T>
vec1d<T> vec1d<T>::merge(vec1d<T> vec) const {

	big_size_t new_size = this->size() + vec.size();

	vec1d<T> res_vec(new_size);

	for (big_size_t i = 0; i < this->size(); i++) {

		res_vec[i] = this->operator [](i);
	}

	for (big_size_t i = this->size(); i < new_size; i++) {

		res_vec[i] = vec[i - this->size()];
	}

	return res_vec;
}

template<typename T>
vec1d<T> vec1d<T>::pad(big_size_t begin, big_size_t pad_size, T pad_val,
		T step) const {

	if (begin >= this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::pad(...)");
	}

	vec1d<T> pad_vec(pad_size, pad_val);
	pad_vec.cumstep(step);

	vec1d<T> slice0 = this->slice(0, begin);
	vec1d<T> slice1 = this->slice(begin, this->size());

	return slice0.merge(pad_vec).merge(slice1);
}

template<typename T>
vec1d<T> vec1d<T>::pad(big_size_t begin, big_size_t pad_size) const {

	if (begin >= this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::pad(...)");
	}

	T pad_val;

	if (begin == 0) {

		pad_val = this->operator[](begin);
	}

	else {

		pad_val = this->operator[](begin - 1);
	}

	vec1d<T> pad_vec(pad_size, pad_val);
	vec1d<T> slice0 = this->slice(0, begin);
	vec1d<T> slice1 = this->slice(begin, this->size());

	return slice0.merge(pad_vec).merge(slice1);
}

// ====================================================================

template<typename T>
void vec1d<T>::write_in_range(big_size_t begin, big_size_t end,
		std::function<void(T &vec_i)> custom_func) {

	if (begin > end || end > this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::write_in_range(...)");
	}

	for (big_size_t i = begin; i < end; i++) {
		custom_func(this->operator [](i));
	}
}

template<typename T>
void vec1d<T>::apply_in_range(big_size_t begin, big_size_t end,
		std::function<T(T vec_i)> custom_func) {

	if (begin > end || end > this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::apply_in_range(...)");
	}

	for (big_size_t i = begin; i < end; i++) {
		this->operator [](i) = custom_func(this->operator [](i));
	}
}

template<typename T>
void vec1d<T>::slice_assign(const vec1d<T> &vec) {

	big_size_t size = std::min(this->size(), vec.size());

	for (big_size_t i = 0; i < size; i++) {

		this->operator [](i) = vec[i];
	}

}

template<typename T>
T vec1d<T>::min(big_size_t begin, big_size_t end) const {

	if (begin > end || end > this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::min(...)");
	}

	T min_val = std::numeric_limits<T>::max();

	for (big_size_t i = begin; i < end; i++) {

		min_val = std::min(min_val, this->operator [](i));
	}

	return min_val;
}

template<typename T>
T vec1d<T>::max(big_size_t begin, big_size_t end) const {

	if (begin > end || end > this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::max(...)");
	}

	T max_val = std::numeric_limits<T>::min();

	for (big_size_t i = begin; i < end; i++) {

		max_val = std::max(max_val, this->operator [](i));
	}

	return max_val;
}

template<typename T>
template<typename RT>
RT vec1d<T>::sum(big_size_t begin, big_size_t end) const {

	if (begin > end || end > this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::sum(...)");
	}

	RT sum = 0;

	for (big_size_t i = begin; i < end; i++) {

		sum += this->operator [](i);
	}

	return sum;
}

template<typename T>
template<typename RT>
RT vec1d<T>::multiply(big_size_t begin, big_size_t end) const {

	if (begin > end || end > this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::multiply(...)");
	}

	RT result = 1;

	for (big_size_t i = begin; i < end; i++) {
		result *= this->operator [](i);
	}

	return result;
}

template<typename T>
vec1d<T> vec1d<T>::reduce_multiply(big_size_t begin, big_size_t end) const {

	if (begin > end || end > this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::reduce_multiply(...)");
	}

	big_size_t new_size = this->size() - (end - begin) + 1;
	vec1d<T> res_vec(new_size);

	T result = 1;

	for (big_size_t i = begin; i < end; i++) {
		result *= this->operator [](i);
	}

	for (big_size_t i = 0; i < begin; i++) {

		res_vec[i] = this->operator [](i);
	}

	big_size_t j = begin + 1;

	for (big_size_t i = end; i < this->size(); i++) {

		res_vec[j++] = this->operator [](i);
	}

	// new_size > begin
	res_vec[begin] = result;

	return res_vec;
}

template<typename T>
bool vec1d<T>::is_sorted(big_size_t begin, big_size_t end) const {

	if (begin > end || end > this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::is_sorted(...)");
	}

	for (big_size_t i = begin + 1; i < end; i++) {

		if (this->operator[](i) < this->operator[](i - 1)) {
			return false;
		}
	}

	return true;
}

template<typename T>
void vec1d<T>::cumstep(T step) {

	for (big_size_t i = 1; i < this->size(); i++) {

		this->operator[](i) = this->operator[](i - 1) + step;
	}
}

template<typename T>
void vec1d<T>::print_vec1d(big_size_t begin, big_size_t end) {

	if (begin > end || end > this->size()) {

		throw std::logic_error("Invalid Range, vec1d<T>::print_vec1d(...)");
	}

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
