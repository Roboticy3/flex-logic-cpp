#pragma once

#include <string>

#include "collections/span.h"
#include "collections/llabeling.h"
#include "circuit/gate.h"

/*
A pin connects to a list of nets and holds a state
*/
template<typename S>
struct pin {
  bool valid;
  span<ll> nets;
  S state;
};

/*
A net connects to a list of pins and holds a gate type, indexed by tid

A valid net must always have non-empty pins.
*/
struct net {
  span<ll> pins;
  ll tid;
};

template<typename S, typename T>
struct circuit {
  Labeling<net> netlist;
  Labeling<pin<S>> pinlist;
  Labeling<gate<span<pin<S>>,S,T>> gatetypes;

  inline ll find_type_name(std::string name) {
    for (int i = 0; i < gatetypes.size(); i++) {
      auto g = gatetypes[i];
      if (g.name == name) {
        return i;
      }
    }
  }
};

