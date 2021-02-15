/*
 * linalg.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./linalg.hpp"

template<typename T>
nd::matrix<T> nd::linalg::eye(shape_t shape) {

	nd::matrix<T> mat(shape, 0);
	big_size_t k = 0;

	for (big_size_t i = 0; i < mat.size() - k; i += mat.step_size(), k++) {
		mat.data[i + k] = allocator::val_to_shared_ptr<T>(1);
	}

	return mat;
}

template<typename T>
nd::matrix<T> nd::linalg::matmul(nd::matrix<T> mat1, nd::matrix<T> mat2) {

	max_size_t ndim_1 = mat1.ndim();
	max_size_t ndim_2 = mat2.ndim();

	if (!(ndim_1 >= 2 && ndim_2 >= 2)) {

		throw nd::exception(
				"Input dimension have to be greater than or equal 2, ndim >= 2");
	}

	max_size_t dim01 = mat1.shape()[ndim_1 - 1];
	max_size_t dim11 = mat1.shape()[ndim_1 - 2];

	max_size_t dim02 = mat2.shape()[ndim_2 - 1];
	max_size_t dim12 = mat2.shape()[ndim_2 - 2];

	if (dim01 != dim12) {

		throw nd::exception("Input: mismatch dimension 0");
	}

	shape_t new_shape;

	big_size_t n_chunk = 0;

	big_size_t chunk_size_1 = 0;
	big_size_t chunk_size_2 = 0;

	if (ndim_1 == ndim_2) { // else max(ndim_1, ndim_2)

		for (max_size_t i = 0; i < ndim_1 - 2; i++) {
			if (mat1.shape()[i] != mat2.shape()[i]) {
				throw nd::exception("Inputs: could not be broadcast, "
						"shapes are not aligned for: ndim > 2, ");
			}
		}

		new_shape = std::move(mat1.shape());
		new_shape[ndim_1 - 1] = dim02;

		n_chunk = mat1.shape().multiply(0, ndim_1 - 2);

		if (ndim_1 >= 3) {

			chunk_size_1 = mat1.strides()[ndim_1 - 3];
			chunk_size_2 = mat2.strides()[ndim_2 - 3];
		}
	}

	if (ndim_1 > ndim_2) {

		for (max_size_t i = 0; i < ndim_2 - 2; i++) {
			if (mat1.shape()[i] != mat2.shape()[i]) {
				throw nd::exception("mat1: Inputs: could not be broadcast, "
						"shapes are not aligned for: ndim > 2, ");
			}
		}

		new_shape = std::move(mat1.shape());
		new_shape[ndim_1 - 1] = dim02;

		n_chunk = mat1.shape().multiply(0, ndim_1 - 2);

		chunk_size_1 = mat1.strides()[ndim_1 - 3];

		if (ndim_2 >= 3) {

			chunk_size_2 = mat2.strides()[ndim_2 - 3];
		}

		else {
			chunk_size_2 = 0;
		}
	}

	if (ndim_1 < ndim_2) {

		for (max_size_t i = 0; i < ndim_1 - 2; i++) {
			if (mat1.shape()[i] != mat2.shape()[i]) {
				throw nd::exception("mat2: Inputs: could not be broadcast, "
						"shapes are not aligned for: ndim > 2, ");
			}
		}

		new_shape = std::move(mat2.shape());
		new_shape[ndim_1 - 1] = dim02;

		n_chunk = mat2.shape().multiply(0, ndim_2 - 2);

		if (ndim_1 >= 3) {

			chunk_size_1 = mat1.strides()[ndim_1 - 3];
		} else {
			chunk_size_1 = 0;
		}

		chunk_size_2 = mat2.strides()[ndim_2 - 3];

	}

	nd::matrix<T> result(new_shape);

	big_size_t index = 0;

	for (big_size_t t = 0; t < n_chunk; t++) {

		big_size_t s1 = t * chunk_size_1;
		big_size_t s2 = t * chunk_size_2;

		for (big_size_t d11 = 0; d11 < dim11; d11++) {

			for (big_size_t d02 = 0; d02 < dim02; d02++) {

				vec1d<T> element(dim12);

				for (big_size_t d12 = 0; d12 < dim12; d12++) {

					big_size_t l1 = s1 + (d12 + d11 * dim01);
					big_size_t l2 = s2 + (d02 + d12 * dim02);

					element[d12] = (*mat1.data[l1]) * (*mat2.data[l2]);

				}

				T sum = element.sum(0, dim12);
				result.data[index++] = allocator::val_to_shared_ptr<T>(sum);
			}
		}

	}

	return result;
}

template<typename T>
nd::matrix<T> nd::linalg::dot(nd::matrix<T> mat1, nd::matrix<T> mat2) {

	max_size_t ndim_1 = mat1.ndim();
	max_size_t ndim_2 = mat2.ndim();

	if (!(ndim_1 >= 2 && ndim_2 >= 2)) {

		throw nd::exception(
				"Input dimension have to be greater than or equal 2, ndim >= 2");
	}

	if (ndim_1 == 2 || ndim_2 == 2) {

		throw nd::exception(
				"Input dimension < 2, consider using nd::matrix<T>::matmul instead");
	}

	max_size_t dim01 = mat1.shape()[ndim_1 - 1];

	max_size_t dim02 = mat2.shape()[ndim_2 - 1];
	max_size_t dim12 = mat2.shape()[ndim_2 - 2];

	if (dim01 != dim12) {

		throw nd::exception("Input: mismatch dimension 0");
	}

	shape_t shape_1 = std::move(mat1.shape());
	shape_t shape_2 = std::move(mat2.shape());

	max_size_t new_ndim = ndim_1 + ndim_2 - 2;
	shape_t new_shape(new_ndim);

	for (max_size_t i = 0; i < ndim_1 - 1; i++) {

		new_shape[i] = shape_1[i];
	}

	for (max_size_t i = 0; i < ndim_2 - 2; i++) {

		new_shape[ndim_1 + i - 1] = shape_2[i];
	}

	new_shape[new_ndim - 1] = shape_2[ndim_2 - 1];

	// mat2
	max_size_t step_02 = mat2.strides()[ndim_2 - 2];
	max_size_t step_12 = mat2.strides()[ndim_2 - 1];

	big_size_t steps_2 = 1;
	big_size_t chunk_size_2 = 1;

	big_size_t ij = 0;
	big_size_t slice_2 = 0;

	if (ndim_2 > 2) {

		steps_2 = mat2.size() / mat2.strides()[ndim_2 - 3];
		chunk_size_2 = (dim02 * dim12);
	}

	// mat1
	max_size_t step_size_1 = mat1.step_size();

	big_size_t steps_1 = mat1.size() / step_size_1;

	// ...
	vec1d<T> elems(dim12);
	big_size_t index = 0;

	nd::matrix<T> result(new_shape);

	for (big_size_t d0 = 0; d0 < steps_1; d0++) {

		big_size_t start = d0 * step_size_1;

		for (big_size_t k = 0; k < steps_2; k++) {

			slice_2 = k * chunk_size_2;

			for (max_size_t d02 = 0; d02 < dim02; d02++) {

				for (max_size_t d12 = 0; d12 < dim12; d12++) {

					ij = slice_2 + d02 * step_12 + d12 * step_02;

					elems[d12] = (*mat1.data[start + d12]) * (*mat2.data[ij]);
				}

				T sum = elems.sum(0, dim12);
				result.data[index++] = allocator::val_to_shared_ptr<T>(sum);
			}
		}
	}

	return result;
}

template<typename T>
nd::matrix<T> nd::linalg::transpose(nd::matrix<T> mat, shape_t axes) {

	return mat.permute(axes).copy();
}
