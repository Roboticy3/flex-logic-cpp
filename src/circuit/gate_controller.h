#pragma once

#include <string>

#include "collections/llabeling.h"
#include "circuit/circuit.h"

template<typename S, typename T>
class gate_controller {
  circuit<S, T> *gc;

  public:
    ll add_gate(std:string name);
    bool remove_gate(ll gid);
};