#pragma once

#include "collections/span.h"
#include "collections/llabeling.h"

template<typename S>
struct pin {
  span<ll> nets;
  bool valid;
  S state;
};