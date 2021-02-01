/*
 * generator.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./generator.hpp"

template<typename T>
std::function<T()> generator<T>::bind_mt19937(
		uniform_generator<T> &distribution) {

	std::function<T()> generate = std::bind(distribution, std::ref(e_19937));

	return generate;
}

template<typename T>
std::function<T()> generator<T>::bind_mt19937(
		normal_generator<T> &distribution) {

	std::function<T()> generate = std::bind(distribution, std::ref(e_19937));

	return generate;
}

template<typename T>
T generator<T>::random_uniform(T low, T high) {

	uniform_generator<T> distribution(low, high);

	return bind_mt19937(distribution)();
}

template<typename T>
T generator<T>::random_normal(T mean, T sigma) {

	normal_generator<T> distribution(mean, sigma);

	return bind_mt19937(distribution)();
}
