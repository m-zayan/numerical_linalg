/*
 * Iterator.hpp
 *
 *      Author: Z. Mohamed
 */

#ifndef SRC_ITERATORS_ITERATOR_HPP
#define SRC_ITERATORS_ITERATOR_HPP

#include "../shapes/coords.hpp"

/* ################################################################################## */

#define IMAX_FLIPFLOPS 8
#define IMAX_BIT 4
#define IMAX_AUX1D 4

/* ################################################################################## */

#define RESET_IN_RANGE(arr, l, r, value) do { \
	std::fill(std::begin(arr) + l, std::begin(arr) + r, value); \
} while(0)

#define RESET_ALL(arr, value) do { \
	std::fill(std::begin(arr), std::end(arr), value); \
} while(0)

#define CLEAR_ALL(arr) do { \
	std::fill(std::begin(arr), std::end(arr), 0); \
} while(0)

/* ################################################################################## */

#define ABS(a) \
	((a >= 0) ? a : (-a))

#define MIN(a, b) \
	((a > b) ? b : a)

#define	AXISMOD(ax, v) \
	(ax >= v ? ax - v: 0)

#define SAFEMOVEAXIS(ax) do { \
	ax == 0 ? ax : --ax; \
} while(0)

/* ################################################################################## */

namespace nd::iterator {

struct Iterator {

	shape_t default_shape;
	strides_t default_strides;

	strides_t default_bounds;

	shape_t default_current;

	// ==============================================

	max_size_t ndim;

	IteratorType iter_type;

	big_size_t index1d;

	big_size_t niter;

	max_size_t iaxis;

	// ==============================================

	max_size_t *shape;
	big_size_t *strides;

	big_size_t *bounds;

	max_size_t *current;

	// ==============================================

	// flags
	bool bit[IMAX_BIT];

	// auxiliary index1d
	big_size_t aux1d[IMAX_AUX1D];

	// auxiliary state
	big_t flipflop[IMAX_FLIPFLOPS];

	Iterator() = delete;
	Iterator(const Iterator &it) = delete;
	Iterator(const Iterator &&it) = delete;

	Iterator(const coords &attr);

	void reset();

	void reset_ref();

	void reinterpret_coords(const coords &attr);

	/* [current & shape] <arg> must be a non-temporary */
	void reinterpret_slice(shape_t &current, shape_t &shape);

	void reinterpret_linear();
	void reinterpret_none();
	void reinterpret_none(big_size_t size);

	virtual ~Iterator() = default;
};

/* ===================================================================== */

inline Iterator::Iterator(const coords &attr) {

	iter_type = attr.iter_type;
	ndim = attr.ndim;

	default_shape = attr.shape;
	default_strides = attr.strides;

	// ==============================================

	default_bounds = get_bounds(default_shape, default_strides);

	// ==============================================

	index1d = 0;

	default_current = shape_t(this->ndim, 0);

	niter = attr.size1d;
	iaxis = ndim;

	SAFEMOVEAXIS(iaxis);

	// ==============================================

	shape = default_shape.ref(0);
	strides = default_strides.ref(0);
	bounds = default_bounds.ref(0);
	current = default_current.ref(0);

	// ==============================================

	CLEAR_ALL(bit);
	CLEAR_ALL(aux1d);
	CLEAR_ALL(flipflop);
}

inline void Iterator::reset() {

	default_current.fill(0);

	default_bounds = get_bounds(default_shape, default_strides);

	index1d = 0;

	iaxis = ndim;

	SAFEMOVEAXIS(iaxis);

	niter = get_size1d(default_shape);

	this->reset_ref();

	// ==============================================

	CLEAR_ALL(bit);
	CLEAR_ALL(aux1d);
	CLEAR_ALL(flipflop);
}

inline void Iterator::reset_ref() {

	shape = default_shape.ref(0);
	strides = default_strides.ref(0);
	bounds = default_bounds.ref(0);
	current = default_current.ref(0);
}

inline void Iterator::reinterpret_coords(const coords &attr) {

	iter_type = attr.iter_type;
	ndim = attr.ndim;

	niter = attr.size1d;

	default_shape = attr.shape;
	default_strides = attr.strides;
	default_bounds = get_bounds(default_shape, default_strides);

	this->reset();
}

inline void Iterator::reinterpret_slice(shape_t &current, shape_t &shape) {

	this->current = current.ref(0);
	this->shape = shape.ref(0);

	ndim = shape.size();
}

inline void Iterator::reinterpret_linear() {
	iter_type = IteratorType::Linear;
}

inline void Iterator::reinterpret_none() {
	iter_type = IteratorType::None;
}

inline void Iterator::reinterpret_none(big_size_t size) {

	this->reinterpret_none();

	niter = size;
}

}

/* ################################################################################## */

#define ITER_LIKE_SCALAR(it) (it->iter_type == IteratorType::Scalar)
#define ITER_LIKE_NONE(it) (it->iter_type == IteratorType::None)
#define ITER_LIKE_LINEAR(it) (it->iter_type == IteratorType::Linear)
#define ITER_LIKE_PAIR(it) (it->iter_type == IteratorType::Pair)

/* ################################################################################## */

#define ITER_RESET_IAXIS1(it) do { \
	it->iaxis = it->ndim; \
	SAFEMOVEAXIS(it->iaxis); \
} while(0)

#define ITER_RESET_IAXIS2(it0, it1) do { \
	ITER_RESET_IAXIS1(it0); \
	ITER_RESET_IAXIS1(it1); \
} while(0)

#define ITER_SET_IAXIS1(it, i) do { \
	it->iaxis = i; \
} while(0)

#define ITER_SET_IAXIS2(it0, it1, i) do { \
	ITER_SET_IAXIS1(it0, i); \
	ITER_SET_IAXIS1(it1, i); \
} while(0)

// ------------------------------------------------------

#define ITER_FORWARD(it, i) do { \
	it->index1d += (it->current[i] * it->strides[i]); \
} while(0)

#define ITER_BACKWARD(it, i) do { \
	it->index1d -= (it->current[i] * it->strides[i]); \
} while(0)

// ------------------------------------------------------

#define ITER1D_MUST_RESET(it) do { \
	if(it->index1d >= it->niter){ \
	  it->index1d = 0; \
    } \
} while(0)

// ------------------------------------------------------

#define ITER_IS_VALID_STEP(it) \
	(it->current[it->iaxis] + 1 < it->shape[it->iaxis])

#define ITER_UPDATE_STEP(it) do { \
	it->index1d += it->strides[it->iaxis]; \
	it->current[it->iaxis]++; \
	it->bit[0] = true; \
} while(0)

#define ITER_CLIP_STEP(it) do{ \
	it->index1d -= it->bounds[it->iaxis]; \
	it->current[it->iaxis] = 0; \
	it->bit[0] = false; \
} while(0)

// ------------------------------------------------------

#define ITER_NEXT_AT(it) do { \
	if (ITER_IS_VALID_STEP(it)) { \
		ITER_UPDATE_STEP(it); \
	} else { \
		ITER_CLIP_STEP(it); \
	} \
} while(0)

#define ITER_NEXT(it) do { \
	if(ITER_LIKE_NONE(it)) { \
		it->index1d++; \
		ITER1D_MUST_RESET(it); \
	}\
	else if(!ITER_LIKE_SCALAR(it)) { \
		ITER_RESET_IAXIS1(it); \
		for (; it->iaxis > 0; --it->iaxis) { \
			if (ITER_IS_VALID_STEP(it)) { \
				ITER_UPDATE_STEP(it); \
				break; \
			} else { \
				ITER_CLIP_STEP(it); \
			} \
		} \
		if(it->iaxis == 0){ \
			ITER_NEXT_AT(it); \
		} \
	} \
} while(0)

/* ################################################################################## */

#define ITER_CHUNK_NEXT_AT(it) do { \
	if (it->shape[it->iaxis] == 1) { \
		ITER_CLIP_STEP(it); \
	} else { \
		ITER_UPDATE_STEP(it); \
	} \
} while(0)

// ------------------------------------------------------

#define ITER_LIKE_PAIRWISE3_NEXT(out_it, it0, it1) do { \
	ITER_NEXT(out_it); \
	ITER_RESET_IAXIS2(it0, it1); \
	for (; it0->iaxis > out_it->iaxis; --it0->iaxis, --it1->iaxis) { \
		ITER_CLIP_STEP(it0); \
		ITER_CLIP_STEP(it1); \
	} \
	if(out_it->bit[0]) { \
		ITER_CHUNK_NEXT_AT(it0); \
		ITER_CHUNK_NEXT_AT(it1); \
	} else { \
		ITER_CLIP_STEP(it0); \
		ITER_CLIP_STEP(it1); \
	} \
} while(0)

#define ITER_LIKE_PAIRWISE2_NEXT(out_it, it) do { \
	ITER_NEXT(out_it); \
	ITER_RESET_IAXIS1(it); \
	for (; it->iaxis > out_it->iaxis; --it->iaxis) { \
		ITER_CLIP_STEP(it); \
	} \
	if(out_it->bit[0]) { \
		ITER_CHUNK_NEXT_AT(it); \
	} else { \
		ITER_CLIP_STEP(it); \
	} \
} while(0)

// ------------------------------------------------------

#define ITER_PAIRWISE3_NEXT(out_it, it0, it1) do { \
	if(ITER_LIKE_PAIR(out_it)) { \
		ITER_LIKE_PAIRWISE3_NEXT(out_it, it0, it1); \
	} else { \
		ITER_NEXT(out_it); \
		ITER_NEXT(it0); \
		ITER_NEXT(it1); \
	} \
} while(0)

#define ITER_PAIRWISE2_NEXT(out_it, it) do { \
	if(ITER_LIKE_PAIR(out_it)) { \
		ITER_LIKE_PAIRWISE2_NEXT(out_it, it); \
	} else { \
		ITER_NEXT(out_it); \
		ITER_NEXT(it); \
	} \
} while(0)

/* ################################################################################## */

#define ITER_MOVE_TO1D(it, indices) do { \
	it->index1d = 0; \
	ITER_SET_IAXIS1(it, 0); \
	for(; it->iaxis<it->ndim; it->iaxis++){ \
		it->index1d += (it->strides[it->iaxis] * indices[it->iaxis]); \
	} \
} while(0)

/* pcindex: [placeholder-index1d] */
#define ITER_INDEX_AT1D(it, indices, pcindex) do { \
	pcindex = 0; \
	ITER_SET_IAXIS1(it, 0); \
	for(; it->iaxis<it->ndim; it->iaxis++){ \
		pcindex += (it->strides[it->iaxis] * indices[it->iaxis]); \
	} \
} while(0)

/* ################################################################################## */

/* --- [bidirectional] --- */

#define BITER_IS_ROT(it, index1d) (it->bit[1] && it->aux1d[1] >= index1d)

// ------------------------------------------------------

#define BITER_ROTATE(it) do { \
	it->bit[1] = !(it->bit[1]); \
} while(0)

#define BITER_ROTATE_AT(it, begin, end) do { \
	if(it->bit[1]) { \
		ITER_INDEX_AT1D(it, begin, it->aux1d[0]); \
		ITER_INDEX_AT1D(it, end, it->aux1d[1]); \
	} \
} while(0)

// ------------------------------------------------------

/* pcindex: [placeholder-index1d] */
#define BITER_INDEX_AT1D(it, indices, pcindex) do { \
	ITER_INDEX_AT1D(it, indices, pcindex); \
	if(BITER_IS_ROT(it, pcindex)) { \
		pcindex = it->aux1d[1] - pcindex; \
		pcindex += it->aux1d[0]; \
	} \
} while(0)

/* ################################################################################## */

/* --- [diagonal-] ---
 *
 *	coords must be a 3d view
 */

#define DI3_AXIS(it) \
	((it->flipflop[0] > 0) ? 2 : 1)

#define DI3_IVAXIS(it) \
	((it->flipflop[0] > 0) ? 1 : 2)

// ------------------------------------------------------

#define DI3_SHAPE(it) \
	(it->shape[DI3_AXIS(it)])

#define DI3_IVSHAPE(it) \
	(it->shape[DI3_IVAXIS(it)])

#define DI3_STRIDES(it) \
	(it->strides[DI3_AXIS(it)])

#define DI3_IVSTRIDES(it) \
	(it->strides[DI3_IVAXIS(it)])

// ------------------------------------------------------

#define DI3_DIMSIZE(it) \
	AXISMOD(DI3_SHAPE(it), ABS(it->flipflop[0]))

#define DI3_NITER2(it) \
	MIN(DI3_DIMSIZE(it), DI3_IVSHAPE(it))

#define DI3_NITER3(it) \
	(it->shape[0])

#define DI3_INDEX(it) \
	(ABS(it->flipflop[0]) * DI3_STRIDES(it))

#define DI3_MUST_RESET(it) do { \
	if(it->index1d >= it->niter) { \
		DI3_RESET_INDEX3(it); \
	} \
} while(0)

// ------------------------------------------------------

#define DI3_RESET_INDEX2(it) do { \
	it->current[1] = 0; \
	it->current[2] = 0; \
	it->index1d = DI3_INDEX(it); \
} while(0)

#define DI3_RESET_INDEX3(it) do { \
	it->current[0] = 0; \
	it->current[1] = 0; \
	it->current[2] = 0; \
	it->index1d = DI3_INDEX(it); \
} while(0)

// ------------------------------------------------------

#define DI3_MOVE_ALONG(it, dshift) do { \
	it->flipflop[0] = dshift; \
	DI3_RESET_INDEX3(it); \
	it->flipflop[1] = DI3_NITER2(it); \
} while(0)

// ------------------------------------------------------

#define DI3_IS_NEXT3(it) \
	((it->flipflop[1] <= it->current[1] + 1) || \
			(it->flipflop[1] <= it->current[2] + 1))

// ------------------------------------------------------

#define DI3_NEXT2(it) do { \
	it->current[1]++; \
	it->current[2]++; \
	it->index1d += it->strides[1]; \
	it->index1d += it->strides[2]; \
} while(0)

#define DI3_NEXT3(it) do { \
	DI3_RESET_INDEX2(it); \
	it->current[0]++; \
	ITER_FORWARD(it, 0); \
} while(0)

// ------------------------------------------------------

#define DI3_NEXT(it) do { \
	if(DI3_IS_NEXT3(it)) { \
		DI3_NEXT3(it); \
	} else { \
		DI3_NEXT2(it); \
	} \
	DI3_MUST_RESET(it); \
} while(0)

// ------------------------------------------------------

/* Caching the current state of DI3 */
#define DI3_WAIT(it) do { \
	it->flipflop[2] = it->current[0]; \
	it->flipflop[3] = it->current[1]; \
	it->flipflop[4] = it->current[2]; \
	it->aux1d[2] = it->index1d; \
} while(0)

/* Reset DI3 state */
#define DI3_RELEASE(it) do { \
	it->current[0] = it->flipflop[2]; \
	it->current[1] = it->flipflop[3]; \
	it->current[2] = it->flipflop[4]; \
	it->index1d = it->aux1d[2]; \
} while(0)

// ------------------------------------------------------

/* point-to <--> (k, rindex, i) */
#define DI3_TOR(it, rindex) do { \
	ITER_BACKWARD(it, 1); \
	it->current[1] = rindex; \
	ITER_FORWARD(it, 1); \
} while(0)

/* point-to <--> (k, i, cindex) */
#define DI3_TOC(it, cindex) do { \
	ITER_BACKWARD(it, 2); \
	it->current[2] = cindex; \
	ITER_FORWARD(it, 2); \
} while(0)

#endif /* SRC_ITERATORS_ITERATOR_HPP */
