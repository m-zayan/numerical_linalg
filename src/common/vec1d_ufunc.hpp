/*
 * _v_func.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_COMMON__V_FUNC_HPP
#define SRC_COMMON__V_FUNC_HPP

#include <functional>

namespace _ops {

// ========== vec1d <----> val

namespace v1v {
template<typename T1, typename T2>
std::function<std::function<void(T1&)>(T2 val)> mul = [](T2 val) {

	std::function<void(T1&)> write_func = [val](T1 &vec_i) {

		vec_i *= val;
	};

	return write_func;
};

template<typename T1, typename T2>
std::function<std::function<void(T1&)>(T2 val)> div = [](T2 val) {

	std::function<void(T1&)> write_func = [val](T1 &vec_i) {

		vec_i /= val;
	};

	return write_func;
};

template<typename T1, typename T2>
std::function<std::function<void(T1&)>(T2 val)> add = [](T2 val) {

	std::function<void(T1&)> write_func = [val](T1 &vec_i) {

		vec_i += val;
	};

	return write_func;
};

template<typename T1, typename T2>
std::function<std::function<void(T1&)>(T2 val)> sub = [](T2 val) {

	std::function<void(T1&)> write_func = [val](T1 &vec_i) {

		vec_i -= val;
	};

	return write_func;
};

}

}

#endif /* SRC_COMMON__V_FUNC_HPP_ */
