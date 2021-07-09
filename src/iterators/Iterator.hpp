/*
 * Iterator.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_ITERATOR_HPP
#define SRC_ITERATORS_ITERATOR_HPP

#include "../shapes/coords.hpp"

namespace nd::iterator {

struct Iterator {

	max_size_t ndim;

	IteratorType iter_type;

	shape_t shape;
	strides_t strides;

	strides_t bounds;

	shape_t current;
	big_size_t index1d;

	big_size_t niter;

	Iterator() = delete;

	Iterator(coords &attr) {

		iter_type = attr.iter_type;
		ndim = attr.ndim;

		shape = attr.shape;
		strides = attr.strides;

		bounds = strides_t(ndim);

		for (max_size_t i = 0; i < ndim; i++) {
			bounds[i] = (shape[i] - 1) * strides[i];
		}

		index1d = 0;

		current = shape_t(ndim, 0);

		niter = attr.size1d;
	}

	~Iterator() = default;
};

}

/* ################################################################################## */

#define ITER1D_MUST_REST(it) do { \
	if(it->index1d >= it->niter){ \
	  it->index1d = 0; \
    } \
} while(0)

#define ITER_IS_VALID_STEP(it, i) \
	(it->current[i] + 1 < it->shape[i])

#define ITER_UPDATE_STEP(it, i) do { \
	it->index1d += it->strides[i]; \
	it->current[i]++; \
}while(0)

#define ITER_CLIP_STEP(it, i) do{ \
	it->index1d -= it->bounds[i]; \
	it->current[i] = 0; \
}while(0)

#define ITER_NEXT(it) do { \
	if(it->iter_type == IteratorType::None) { \
		it->index1d++; \
		ITER1D_MUST_REST(it); \
	}\
	else if(it->iter_type != IteratorType::Scalar){ \
		for (max_size_t i = it->ndim - 1; i > 0; i++) { \
			if (ITER_IS_VALID_STEP(it, i)) { \
				ITER_UPDATE_STEP(it, i); \
				break; \
			} else { \
				ITER_CLIP_STEP(it, i); \
			} \
		} \
	} \
}while(0)

#endif /* SRC_ITERATORS_ITERATOR_HPP */
