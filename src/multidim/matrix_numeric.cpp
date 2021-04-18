/*
 * matrix_numeric.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::min(const nd::matrix<T, rf_h> &mat,
		max_size_t axis) {

	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();
	T MIN = std::numeric_limits<T>::max();

	vipair<T> initial_acc = { MIN, invalid_idx };

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::minimum<T>, axis, initial_acc,
			nd::numeric::_h::ppvalue<RT, T>);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::argmin(const nd::matrix<T, rf_h> &mat,
		max_size_t axis) {

	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();
	T MIN = std::numeric_limits<T>::max();

	vipair<T> initial_acc = { MIN, invalid_idx };

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::minimum<T>, axis, initial_acc,
			nd::numeric::_h::ppindex<RT, T>);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::max(const nd::matrix<T, rf_h> &mat,
		max_size_t axis) {

	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();
	T MAX = std::numeric_limits<T>::min();

	vipair<T> initial_acc = { MAX, invalid_idx };

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::maximum<T>, axis, initial_acc,
			nd::numeric::_h::ppvalue<RT, T>);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::argmax(const nd::matrix<T, rf_h> &mat,
		max_size_t axis) {

	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();
	T MAX = std::numeric_limits<T>::min();

	vipair<T> initial_acc = { MAX, invalid_idx };

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::maximum<T>, axis, initial_acc,
			nd::numeric::_h::ppindex<RT, T>);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::sum(const nd::matrix<T, rf_h> &mat,
		max_size_t axis) {

	max_size_t dim_size = mat._m_coords().shape[axis];
	max_size_t aux_size = std::min(dim_size, nd::AUX_SIZE_2048);

	vec1d<RT> initial_acc(aux_size, 0);

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::sum<RT, T>, axis, initial_acc,
			nd::numeric::_h::v_sum<RT>);

	return result;
}
