#pragma once

#include <cstddef>
#include <vector>

/*
Buffers are vectors that should not be moved.
*/
template<typename T>
class Buffer : public std::vector<T> {};

/*
Spans are slices of buffers that are retained when the buffer grows.
*/
template<typename T>
struct span {
  Buffer<T> *base;
  size_t index;
  size_t size;
  
  T& operator[](size_t idx) const noexcept { return base->at(index + idx); }
};