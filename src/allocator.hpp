/*
 * allocator.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_ALLOCATOR_HPP
#define SRC_ALLOCATOR_HPP

#include <memory> // included --> #include <type_traits>


namespace allocator {

template<class T>
struct is_dereferenceable : std::false_type {};

template<class T>
struct is_dereferenceable<std::shared_ptr<T>> : std::true_type {};

template<class T>
struct is_dereferenceable<std::is_pointer<T>> : std::true_type {};

template<typename T>
T* val_to_raw_ptr(T val);

template<typename T>
std::shared_ptr<T> val_to_shared_ptr(T val);

}

#endif /* SRC_ALLOCATOR_HPP */
