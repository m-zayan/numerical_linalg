/*
 * matrix_numeric.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./matrix.hpp"

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::min(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();
	T MIN = std::numeric_limits<T>::max();

	vipair<T> initial_acc = { MIN, invalid_idx };

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::minimum<T>, axis, initial_acc,
			nd::numeric::_h::ppvalue<RT, T>, true, keepdims);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::argmin(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();
	T MIN = std::numeric_limits<T>::max();

	vipair<T> initial_acc = { MIN, invalid_idx };

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::minimum<T>, axis, initial_acc,
			nd::numeric::_h::ppindex<RT, T>, true, keepdims);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::max(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();
	T MAX = std::numeric_limits<T>::min();

	vipair<T> initial_acc = { MAX, invalid_idx };

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::maximum<T>, axis, initial_acc,
			nd::numeric::_h::ppvalue<RT, T>, true, keepdims);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::argmax(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	max_size_t invalid_idx = std::numeric_limits<max_size_t>::max();
	T MAX = std::numeric_limits<T>::min();

	vipair<T> initial_acc = { MAX, invalid_idx };

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::maximum<T>, axis, initial_acc,
			nd::numeric::_h::ppindex<RT, T>, true, keepdims);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::sum(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	max_size_t dim_size = mat._m_coords().shape[axis];
	max_size_t aux_size = nd::mem::clip_dim(dim_size);

	vec1d<RT> initial_acc(aux_size, 0);

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::sum<RT, T>, axis, initial_acc,
			nd::numeric::_h::v_sum<RT>, true, keepdims);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::mean(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	RT dim_size = static_cast<RT>(mat._m_coords().shape[axis]);

	nd::matrix<RT, true> result = nd::numeric::sum<RT>(mat, axis, keepdims)
			/ dim_size;

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::var(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	const uflag8_t bl_tmp = nd::state::BroadcastingLevel;

	// ====================================================

	nd::state::BroadcastingLevel = 2;

	RT dim_size = static_cast<RT>(mat._m_coords().shape[axis]);

	nd::matrix<RT> mmat = static_cast<nd::matrix<RT>>(mat);

	nd::matrix<RT> mu = nd::numeric::mean<RT>(mmat, axis, true);

	mmat = (mmat - mu);

	nd::matrix<RT> result = nd::numeric::sum<RT>(mmat * mmat, axis, keepdims)
			/ dim_size;

	// ====================================================

	nd::state::BroadcastingLevel = bl_tmp;

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::std(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	nd::matrix<RT> var = nd::numeric::var<RT>(mat, axis, keepdims);

	nd::matrix<RT> result = nd::apply<RT, T, true>(var,
			nd::numeric::_h::pow<RT, T, float_auto>(0.5));

	return result;
}
