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
			nd::numeric::_h::ppsum<RT>, true, keepdims);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::mean(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	max_size_t dim_size = mat._m_coords().shape[axis];
	max_size_t aux_size = nd::mem::clip_dim(dim_size);

	vec1d<RT> initial_acc(aux_size, 0);

	RT size = static_cast<RT>(dim_size);

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::sum<RT, T>, axis, initial_acc,
			nd::numeric::_h::ppmean<RT>(size), true, keepdims);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::var(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	max_size_t dim_size = mat._m_coords().shape[axis];
	max_size_t aux_size = nd::mem::clip_dim(dim_size);

	vec1d<vec1d<RT>> initial_acc(aux_size + 1, vec1d<RT>(3, 0));

	initial_acc[0][0] = 1;

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::pair_var<RT, T>, axis, initial_acc,
			nd::numeric::_h::ppair_var<RT>, true, keepdims);

	return result;
}

template<typename RT, typename T, bool rf_h>
nd::matrix<RT, true> nd::numeric::std(const nd::matrix<T, rf_h> &mat,
		max_size_t axis, bool keepdims) {

	vec1d<RT> initial_acc(3, 0);

	nd::matrix<RT, true> result = nd::apply_along_axis(mat,
			nd::numeric::_h::seq_var<RT, T>, axis, initial_acc,
			nd::numeric::_h::ppseq_std<RT>, true, keepdims);

	return result;
}
