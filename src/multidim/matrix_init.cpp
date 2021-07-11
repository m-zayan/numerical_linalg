/*
 * matrix_init.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./matrix.hpp"

template<typename T>
nd::matrix<T> nd::stack(nd::composite<nd::matrix<T, false>> matrix_list) {

	// stack-size
	max_size_t n_chunk = matrix_list.size();

	// element-size
	big_size_t chunk_size;

	if (n_chunk == 0) {

		throw nd::exception(
				"nd::composite<nd::matrix<T>>:: matrix_list is empty");
	}

	for (max_size_t i = 0; i < n_chunk - 1; i++) {

		if (matrix_list[i].shape() != matrix_list[i + 1].shape()
				|| matrix_list[i].ndim() != matrix_list[i + 1].ndim()) {

			throw nd::exception(
					"nd::matrix<T>::stack, matrices must have the same shape");
		}
	}

	max_size_t ndim = matrix_list[0].ndim();
	shape_t shape = matrix_list[0].shape();

	shape_t new_shape(ndim + 1);

	new_shape[0] = n_chunk;

	for (max_size_t i = 0; i < ndim; i++) {

		new_shape[i + 1] = shape[i];
	}

	nd::matrix<T> result(new_shape);

	// [0]
	nd::iterator::Iterator *it = nd::iterator::init_iterator(
			matrix_list[0]._m_coords());

	nd::iterator::Iterator *out_it = nd::iterator::init_iterator(
			result._m_coords());

	T *res = result._m_begin();

	for (max_size_t i = 0; i < n_chunk; i++) {

		if (i > 0) {

			it->reinterpret_coords(matrix_list[i]._m_coords());
		}

		chunk_size = it->niter;

		T *d = matrix_list[i]._m_begin();

		for (big_size_t j = 0; j < chunk_size; j++) {

			res[out_it->index1d] = d[it->index1d];

			ITER_PAIRWISE2_NEXT(out_it, it);
		}
	}

	// [1]
	nd::iterator::free_iterator(it);
	nd::iterator::free_iterator(out_it);

	return result;
}

/* #################################### [random] #################################### */

template<typename T>
nd::matrix<T> nd::random::uniform(T low, T high, shape_t shape) {

	nd::matrix<T> mat(shape);

	T *d = mat._m_begin();

	auto generator_wrapper = generator::random_uniform<T>(low, high);

	for (big_size_t i = 0; i < mat.size(); i++) {

		d[i] = generator_wrapper();
	}

	return mat;
}

