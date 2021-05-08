/*
 * generator.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_RANDOM_GENERATOR_HPP
#define SRC_RANDOM_GENERATOR_HPP

#include <random>
#include <type_traits>
#include <functional>

namespace generator {

static std::mt19937 e_19937 { std::random_device()() };

// gen_type - {0: uniform, 1: normal}

template<bool int_type, int gen_type, typename T> struct generator_t;

template<typename T> struct generator_t<false, 0, T> {
	using generator = typename std::uniform_real_distribution<T>;
};

template<typename T> struct generator_t<true, 0, T> {
	using generator = typename std::uniform_int_distribution<T>;
};

template<typename T> struct generator_t<false, 1, T> {
	using generator = typename std::normal_distribution<T>;
};

template<typename T>
using uniform_generator = typename generator_t<std::is_integral<T>::value, 0, T>::generator;

template<typename T>
using normal_generator = typename generator_t<false, 1, T>::generator;

// ============================================================================================

template<typename T>
inline auto random_uniform(T low, T high) {

	uniform_generator<T> distribution(low, high);

	return std::bind(distribution, std::ref(e_19937));
}

template<typename T>
inline auto random_normal(T mean, T sigma) {

	normal_generator<T> distribution(mean, sigma);

	return std::bind(distribution, std::ref(e_19937));
}

}

#endif /* SRC_RANDOM_GENERATOR_HPP */
