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

	max_size_t iaxis;

	// update-flag
	bool uflag;

	Iterator() = delete;

	Iterator(const coords &attr) {

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
		iaxis = attr.ndim - 1;

		uflag = false;
	}

	~Iterator() = default;
};

}
/* ################################################################################## */
#define ITER_LIKE_SCALAR(it) (it->iter_type == IteratorType::Scalar)
#define ITER_LIKE_NONE(it) (it->iter_type == IteratorType::None)
#define ITER_LIKE_LINEAR(it) (it->iter_type == IteratorType::Linear)
#define ITER_LIKE_PAIR(it) (it->iter_type == IteratorType::Pair)

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
	it->iaxis = i; \
	it->uflag = true; \
}while(0)

#define ITER_CLIP_STEP(it, i) do{ \
	it->index1d -= it->bounds[i]; \
	it->current[i] = 0; \
	it->iaxis = i; \
	it->uflag = false; \
}while(0)

#define ITER_NEXT_AT(it, i) do { \
	if (ITER_IS_VALID_STEP(it, i)) { \
		ITER_UPDATE_STEP(it, i); \
	} else { \
		ITER_CLIP_STEP(it, i); \
	} \
}while(0)

#define ITER_NEXT(it) do { \
	if(ITER_LIKE_NONE(it)) { \
		it->index1d++; \
		ITER1D_MUST_REST(it); \
	}\
	else if(!ITER_LIKE_SCALAR(it)) { \
		max_size_t i; \
		for (i=it->ndim - 1; i > 0; --i) { \
			if (ITER_IS_VALID_STEP(it, i)) { \
				ITER_UPDATE_STEP(it, i); \
				break; \
			} else { \
				ITER_CLIP_STEP(it, i); \
			} \
		} \
		if(i == 0){ \
			ITER_NEXT_AT(it, 0); \
		} \
	} \
}while(0)

/* ################################################################################## */

#define ITER_CHUNK_NEXT_AT(it, i) do { \
	if (it->shape[i] == 1) { \
		ITER_CLIP_STEP(it, i); \
	} else { \
		ITER_UPDATE_STEP(it, i); \
	} \
}while(0)

#define ITER_LIKE_PAIRWISE3_NEXT(out_it, it0, it1) do { \
	ITER_NEXT(out_it); \
	for(max_size_t i=out_it->ndim - 1; i > out_it->iaxis; --i) { \
		ITER_CLIP_STEP(it0, i); \
		ITER_CLIP_STEP(it1, i); \
	} \
	if(out_it->uflag) { \
		ITER_CHUNK_NEXT_AT(it0, out_it->iaxis); \
		ITER_CHUNK_NEXT_AT(it1, out_it->iaxis); \
	} else { \
		ITER_CLIP_STEP(it0, out_it->iaxis); \
		ITER_CLIP_STEP(it1, out_it->iaxis); \
	} \
}while(0)

#define ITER_LIKE_PAIRWISE2_NEXT(out_it, it0) do { \
	ITER_NEXT(out_it); \
	for(max_size_t i=out_it->ndim - 1; i > out_it->iaxis; --i) { \
		ITER_CLIP_STEP(it0, i); \
	} \
	if(out_it->uflag) { \
		ITER_CHUNK_NEXT_AT(it0, out_it->iaxis); \
	} else { \
		ITER_CLIP_STEP(it0, out_it->iaxis); \
	} \
}while(0)

/* ################################################################################## */

#define ITER_PAIRWISE3_NEXT(out_it, it0, it1) do { \
	if(ITER_LIKE_PAIR(out_it)) { \
		ITER_LIKE_PAIRWISE3_NEXT(out_it, it0, it1); \
	} else { \
		ITER_NEXT(out_it); \
		ITER_NEXT(it0); \
		ITER_NEXT(it1); \
	} \
}while(0)

#define ITER_PAIRWISE2_NEXT(out_it, it0) do { \
	if(ITER_LIKE_PAIR(out_it)) { \
		ITER_LIKE_PAIRWISE2_NEXT(out_it, it0); \
	} else { \
		ITER_NEXT(out_it); \
		ITER_NEXT(it0); \
	} \
}while(0)

#endif /* SRC_ITERATORS_ITERATOR_HPP */
