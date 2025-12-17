#pragma once

#include <vector>
#include <queue>

#include "collections/llabeling.h"

template <typename S, typename T>
struct levent {
  T time;
  S signal;
  ll label;

  inline bool operator < (const levent &other) const {
    return time > other.time;
  }
};

template <typename S1, typename S2, typename T>
inline bool compare_levent(levent<S1, T> a, levent<S2, T> b) {
  return a.time > b.time;
}

template<typename S, typename T>
class levents : public std::priority_queue<levent<S, T>> {};