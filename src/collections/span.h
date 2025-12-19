#pragma once

#include <cstddef>

template<typename T>
struct span {
  T* data;
  std::size_t size;
  
  T& operator[](std::size_t idx) const noexcept { return data[idx]; }
};
