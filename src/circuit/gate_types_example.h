#pragma once

#include "collections/span.h"
#include "circuit/circuit.h"
#include "circuit/gate.h"

constexpr const char* EXAMPLE_AND_LABELS[] = {"A", "B", "OUT"};
constexpr const char* EXAMPLE_NOT_LABELS[] = {"A", "OUT"};
constexpr const char* EXAMPLE_LATCH_LABELS[] = {"SET", "RESET", "INNER", "OUT"};

void EXAMPLE_AND_SOLVER(span<pin<int>> pins, levents<int, int> &events, int time) {
  pins[2].state = pins[0].state & pins[1].state;
  events.push(levent<int, int>{time+1, pins[2].state, 0});
}

void EXAMPLE_NOT_SOLVER(span<pin<int>> pins, levents<int, int> &events, int time) {
  pins[1].state = ~pins[0].state;
  events.push(levent<int, int>{time+1, pins[1].state, 1});
}

void EXAMPLE_LATCH_SOLVER(span<pin<int>> pins, levents<int, int> &events, int time) {
  pins[2].state |= pins[0].state;
  pins[2].state &= ~pins[1].state;
  pins[3].state = pins[2].state;
  events.push(levent<int, int>{time+2, pins[3].state, 2});
}

constexpr gate<span<pin<int>>, int, int> EXAMPLE_GATES[] {
  {
    "AND",
    EXAMPLE_AND_SOLVER,
    EXAMPLE_AND_LABELS,
    3
  },
  {
    "NOT",
    EXAMPLE_NOT_SOLVER,
    EXAMPLE_NOT_LABELS,
    2
  },
  {
    "LATCH",
    EXAMPLE_LATCH_SOLVER,
    EXAMPLE_LATCH_LABELS,
    4
  }
};