#pragma once

#include <string>

#include "collections/llabeling.h"
#include "circuit/gate.h"

/*
A pin connects to a list of nets and holds a state

Nets should be sorted by id.
*/
template<typename S>
struct pin {
  bool valid;
  span<ll> nets;
  S state;
};

template<typename S>
inline bool is_empty_default(pin<S> element) {
  return !element.valid;
}

/*
A net connects to a list of pins and holds a gate type, indexed by tid

Pins might not be sorted. When components have a gatetype/pinout, pins are in
the order matching the pinout, which is then used by that net's solver to 
determine which pin is which.

A valid net must always have non-empty pins.
*/
struct net {
  span<ll> pins;
  ll tid;
};

inline bool is_empty_default(net element) {
  return element.pins.base == nullptr || element.pins.base->count() == 0;
}

template<typename S, typename T>
struct circuit {
  Labeling<net> netlist;
  Labeling<pin<S>> pinlist;
  Labeling<gate<span<pin<S>>,S,T>> gatetypes;

  BlockLabeling<ll> netblocks;
  BlockLabeling<ll> pinblock;

  inline ll find_type_name(std::string name) {
    for (int i = 0; i < gatetypes.size(); i++) {
      auto g = gatetypes[i];
      if (g.name == name) {
        return i;
      }
    }
  }

  inline std::vector<ll> view_pins(ll nid) {
    auto p_net = netlist.get(nid);
    if (p_net) {
      return {};
    }

    return p_net->pins.compress();
  }
};

