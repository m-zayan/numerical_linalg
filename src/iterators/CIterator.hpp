/*
 * ### Experimental/Iterator
 *
 * CIterator.hpp
 *
 * 	[core-iterator]
 *
 * 	Author: Z. Mohamed
 *
 *	- Faster Than Other Iterators
 *
 *  - Extended Pairwise Sequential Iterator.
 *
 *  - Designed to fit all nd::matrix<T, ...> - ops
 *  	(i.e. broadcastable and non-broadcastable)
 *
 *  - Multi-ops without intermediate results,
 *
 *    ex. [expression]:
 *
 *    	(mat0 + mat1 - mat2 * mat3 / 2) -->
 *    				(-mat2 * mat3 / 2 + mat0 + mat1) --> result
 */

#ifndef SRC_ITERATORS_CITERATOR_HPP
#define SRC_ITERATORS_CITERATOR_HPP

#include "../shapes/coords.hpp"

class CIterator {

protected:

	vec1d<coords*> attr_refs;

	vec1d<coords> aligned_coords;

	vec1d<max_size_t> axis;
	vec1d<max_size_t> mov_axis;

	vec1d<strides_t> bounds;

	// indices
	vec1d<shape_t> current;

	// index_1d
	vec1d<big_size_t> index1d;

public:

	max_size_t *axis_ref;
	max_size_t *mvaxis_ref;

	coords *caligned_ref;

	strides_t *bounds_ref;
	shape_t *current_ref;
	big_size_t *index1d_ref;

	max_size_t nin_nodes;
	max_size_t nout_nodes;

	max_size_t optree_depth;
	max_size_t optree_size;

	// used for tree traversing [top-down]
	max_size_t troot;

	// used for tree traversing [bottom-up]
	max_size_t bleft;

	// used for tree traversing [top-down | leaf-cache]
	max_size_t tleaf;

	// used for tree traversing [bottom-down | leaf-cache]
	max_size_t bright;

	CIterator() = delete;

	CIterator(vec1d<coords*> &&attr_refs);

	// ------------------------------------------------------------

	void _it_reset_optree_baseindex();

	max_size_t optree_parent(max_size_t i);
	max_size_t optree_lchild(max_size_t i);
	max_size_t optree_rchild(max_size_t i);

	bool is_optree_root(max_size_t i);

	/*
	 * i.e. [op-tree]:
	 *
	 *		- op-tree follows bottom-up approach
	 *
	 * 		- right-child is always a leaf node.
	 * 		- left-child is a subtree (except the most left-child is a leaf).
	 *
	 * 		- op-root != tree-root
	 * 		- op-root = subtree
	 */
	bool is_optree_leaf(max_size_t i);

	// op-tree - is most left-child
	bool is_optree_lend(max_size_t i);

	// ------------------------------------------------------------
	void _it_optree_next();

	void _it_init_leaf();

	void _it_init_state_step(uflag8_t ttype);

	void _it_init_state();
	// ------------------------------------------------------------

	void op_primitive_alignment(std::string &&signature = "");
	void op_2d_alignment(std::string &&signature = "");

	// ------------------------------------------------------------

	/*
	 * ttype <--> {0: top-down-root,
	 * 			   1: top-down-leaf,
	 * 			   2: bottom-up-root,
	 * 			   3: bottom-up-leaf}
	 *
	 */

	max_size_t optree_index(uflag8_t ttype);

	max_size_t& ith_ndim(uflag8_t ttype);

	max_size_t& iaxis(uflag8_t ttype);
	max_size_t& imov_axis(uflag8_t ttype);

	max_size_t& ijshape(uflag8_t ttype, max_size_t dim_index);

	big_size_t& ijstride(uflag8_t ttype, max_size_t dim_index);

	strides_t& ibound(uflag8_t ttype);
	shape_t& icurrent(uflag8_t ttype);

	big_size_t& ijbound(uflag8_t ttype, max_size_t dim_index);
	max_size_t& ijcurrent(uflag8_t ttype, max_size_t dim_index);

	big_size_t& iindex1d(uflag8_t ttype);

	coords root_coords();

	// ------------------------------------------------------------

};

/* #################################################################################### */

CIterator::CIterator(vec1d<coords*> &&attr_refs) {

	max_size_t nin_nodes = attr_refs.size();
	max_size_t nout_nodes = nin_nodes - 1;
	max_size_t optree_size = nin_nodes + nout_nodes;

	this->attr_refs = attr_refs;

	// --------------- [0] ---------------
	this->aligned_coords = vec1d<coords>(optree_size);

	// --------------- [1] ---------------
	this->axis = vec1d<max_size_t>(optree_size);
	this->mov_axis = vec1d<max_size_t>(optree_size);

	// --------------- [2] ---------------
	this->bounds = vec1d<strides_t>(optree_size);
	this->current = vec1d<shape_t>(optree_size);
	this->index1d = vec1d<big_size_t>(optree_size);

	// --------------- [3] ---------------
	this->caligned_ref = this->aligned_coords.ref(0);

	this->axis_ref = this->axis.ref(0);
	this->mvaxis_ref = this->mov_axis.ref(0);

	this->bounds_ref = this->bounds.ref(0);

	this->current_ref = this->current.ref(0);
	this->index1d_ref = this->index1d.ref(0);
	// -----------------------------------

	this->nin_nodes = nin_nodes;
	this->nout_nodes = nout_nodes;

	this->optree_depth = nin_nodes;
	this->optree_size = optree_size;

	// root-node
	this->troot = optree_size - 1;

	// most left node | leaf
	this->bleft = 0;

	this->tleaf = optree_size - 1;
	this->bright = 1;

	/* set-default-alignment */
	// ... [here]
}

/* ============================== [tree-traversing-func] ===============================*/

inline void CIterator::_it_reset_optree_baseindex() {

	this->troot = optree_size - 1;
	this->bleft = 0;

	this->tleaf = optree_size - 1;
	this->bright = 1;
}

inline bool CIterator::is_optree_root(max_size_t i) {

	return (i == this->optree_size - 1);
}

inline bool CIterator::is_optree_leaf(max_size_t i) {

	return (i < this->nin_nodes);
}

inline bool CIterator::is_optree_lend(max_size_t i) {

	return (i == 0);
}

inline max_size_t CIterator::optree_parent(max_size_t i) {

	// case: tree-root-node
	if (is_optree_root(i)) {

		return i;
	}

	else if (is_optree_lend(i)) {

		return this->nin_nodes;
	}

	else if (is_optree_leaf(i)) {

		return this->nin_nodes + i - 1;
	}

	else {

		return i + 1;
	}

}

inline max_size_t CIterator::optree_lchild(max_size_t i) {

	// case: tree-leaf-node
	if (is_optree_leaf(i)) {
		return i;
	}

	else if (i == this->nin_nodes) {
		return 0;
	}

	else {
		return i - 1;
	}
}

inline max_size_t CIterator::optree_rchild(max_size_t i) {

	// case: tree-leaf-node
	if (is_optree_leaf(i)) {
		return i;
	}

	else {
		return i - this->nin_nodes + 1;
	}
}

inline void CIterator::_it_optree_next() {

	// [top-down]
	this->tleaf = this->optree_rchild(this->troot);
	this->troot = this->optree_lchild(this->troot);

	// [bottom-up]
	this->bleft = this->optree_parent(this->bleft);
	this->bright = this->optree_parent(this->bleft);

	if (!is_optree_root(this->bleft)) {
		this->bright = this->optree_rchild(this->bright);
	}
}

inline max_size_t CIterator::optree_index(uflag8_t ttype) {

	if (ttype == 0) {
		return this->troot;
	}

	else if (ttype == 1) {
		return this->tleaf;
	}

	else if (ttype == 2) {
		return this->bleft;
	}

	else {
		return this->bright;
	}
}

/* =====================================================================================*/

inline max_size_t& CIterator::ijshape(uflag8_t ttype, max_size_t dim_index) {

	max_size_t op_index = this->optree_index(ttype);

	return this->caligned_ref[op_index].shape[dim_index];
}

inline big_size_t& CIterator::ijstride(uflag8_t ttype, max_size_t dim_index) {

	max_size_t op_index = this->optree_index(ttype);

	return this->caligned_ref[op_index].strides[dim_index];
}

inline max_size_t& CIterator::ith_ndim(uflag8_t ttype) {

	max_size_t op_index = this->optree_index(ttype);

	return this->caligned_ref[op_index].ndim;
}

inline max_size_t& CIterator::iaxis(uflag8_t ttype) {

	max_size_t op_index = this->optree_index(ttype);

	return this->axis_ref[op_index];
}

inline max_size_t& CIterator::imov_axis(uflag8_t ttype) {

	max_size_t op_index = this->optree_index(ttype);

	return this->mvaxis_ref[op_index];
}

inline strides_t& CIterator::ibound(uflag8_t ttype) {

	max_size_t op_index = this->optree_index(ttype);

	return this->bounds_ref[op_index];
}

inline shape_t& CIterator::icurrent(uflag8_t ttype) {

	max_size_t op_index = this->optree_index(ttype);

	return this->current_ref[op_index];
}

inline big_size_t& CIterator::ijbound(uflag8_t ttype, max_size_t dim_index) {

	max_size_t op_index = this->optree_index(ttype);

	return this->bounds_ref[op_index][dim_index];
}

inline max_size_t& CIterator::ijcurrent(uflag8_t ttype, max_size_t dim_index) {

	max_size_t op_index = this->optree_index(ttype);

	return this->current_ref[op_index][dim_index];
}

inline big_size_t& CIterator::iindex1d(uflag8_t ttype) {

	max_size_t op_index = this->optree_index(ttype);

	return this->index1d_ref[op_index];
}

// ------------------------------------ [init-func] --------------------------------------

inline void CIterator::_it_init_leaf() {

	for (max_size_t i = 0; i < this->nin_nodes; i++) {

		this->caligned_ref[i] = *(this->attr_refs[i]);
	}

}

// [bottom-up init-step]
inline void CIterator::_it_init_state_step(uflag8_t ttype) {

	max_size_t ndim = this->ith_ndim(ttype);

	this->imov_axis(ttype) = ndim - 1;
	this->iaxis(ttype) = ndim - 1;

	this->ibound(ttype) = strides_t(ndim);
	this->icurrent(ttype) = shape_t(ndim, 0);
	this->iindex1d(ttype) = 0;

	for (max_size_t j = 0; j < ndim; j++) {

		this->ijbound(ttype, j) = (this->ijshape(ttype, j) - 1)
				* this->ijstride(ttype, j);
	}

}

// [bottom-up init]
inline void CIterator::_it_init_state() {

	for (max_size_t i = 0; i < this->optree_depth - 1; i++) {

		this->_it_init_state_step(2);
		this->_it_init_state_step(3);

		this->_it_optree_next();
	}

	// root-node
	this->_it_init_state_step(2);

	// reset op-tree index
	this->_it_reset_optree_baseindex();
}

// case: primitive-op | [broadcastable & non-broadcastable]
inline void CIterator::op_primitive_alignment(std::string &&signature) {

	this->_it_init_leaf();

	this->caligned_ref[this->nin_nodes] = nd::align_dim(this->caligned_ref[0],
			this->caligned_ref[1], std::move(signature));

	for (max_size_t i = this->nin_nodes + 1; i < this->optree_size; i++) {

		this->caligned_ref[i] = nd::align_dim(this->caligned_ref[i - 1],
				this->caligned_ref[i - this->nin_nodes + 1],
				std::move(signature));
	}

	this->_it_init_state();
}
// case: matmul-like-op | broadcast
inline void CIterator::op_2d_alignment(std::string &&signature) {

	this->_it_init_leaf();

	this->caligned_ref[this->nin_nodes] = nd::align_dim_2d(
			this->caligned_ref[0], this->caligned_ref[1], std::move(signature));

	for (max_size_t i = this->nin_nodes + 1; i < this->optree_size; i++) {

		this->caligned_ref[i] = nd::align_dim_2d(this->caligned_ref[i - 1],
				this->caligned_ref[i - this->nin_nodes + 1],
				std::move(signature));
	}

	this->_it_init_state();
}

// -------------------------------------------------------------------------------------

inline coords CIterator::root_coords() {

	return this->caligned_ref[this->optree_size - 1];
}
#endif /* SRC_ITERATORS_CITERATOR_HPP */
