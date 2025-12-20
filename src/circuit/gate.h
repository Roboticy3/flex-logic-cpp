#pragma once

#include <string>

#include "collections/llabeling.h"
#include "collections/levents.h"

/*
use a gate's state from pins P to add to event queue levents<S, T>

current time is given by the last argument, T
*/
template<typename P, typename S, typename T>
using gate_solver = void(* const)(P, levents<S, T>&, T);

/*
define a type of gate that can be added to a circuit. Each type can have:

`name` - a string name of the gate type to display to users
`solver` - a function to define the behavior of gates with this type
`pinout` - list of pin names on this gate, can help implement solver
*/
template<typename P, typename S, typename T>
struct gate {
  const char* const name;
  const gate_solver<P, S, T> solver;
  const char* const* pinout;
  const int pin_count;
};