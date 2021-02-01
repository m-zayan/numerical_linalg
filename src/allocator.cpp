/*
 * allocator.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./allocator.hpp"

template<typename T>
T* allocator::val_to_raw_ptr(T val){

	return (new T(val));
}

template<typename T>
std::shared_ptr<T> allocator::val_to_shared_ptr(T val){

	return std::shared_ptr<T>(new T (val));
}

