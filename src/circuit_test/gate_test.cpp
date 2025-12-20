
#include <vector>

#include "test_definitions.h"
#include "circuit_test/gate_test.h"

#include "collections/span.h"
#include "circuit/circuit.h"
#include "circuit/gate_types_example.h"

Buffer<pin<int>> make_test_pins(std::vector<int> states) {
  Buffer<pin<int>> result;

  for (int s : states) {
    result.push_back(pin<int>{
      true,
      {
        { 0 },
        1
      },
      s,
    });
  }

  return result;
}

void test_and() {
  TestSingleton::start("and");
  auto pins = make_test_pins({1, 1, 0}); // Inputs: A=1, B=1, Output=0
  levents<int, int> events;
  
  EXAMPLE_GATES[0].solver(span<pin<int>>{&pins, 0, 3}, events, 0); // AND gate
  
  TestSingleton::assert<int>(pins[2].state, 1, "AND gate output state");
  TestSingleton::assert<size_t>(events.size(), 1, "AND gate event count");
  
  auto event = events.top();
  TestSingleton::assert<int>(event.signal, 1, "AND gate event signal");
  TestSingleton::assert<int>(event.time, 1, "AND gate event time");
  TestSingleton::assert<ll>(event.label, 0, "AND gate event label");
}

void test_or() {
  TestSingleton::start("or");
  auto pins = make_test_pins({1, 1, 0}); // Inputs: A=1, Output=0
  levents<int, int> events;
  
  EXAMPLE_GATES[1].solver(span<pin<int>>{&pins, 0, 2}, events, 0); // NOT gate
  
  TestSingleton::assert<int>(pins[1].state, ~1, "NOT gate output state");
  TestSingleton::assert<int>(events.size(), 1, "NOT gate event count");
  
  auto event = events.top();
  TestSingleton::assert<int>(event.signal, ~1, "NOT gate event signal");
  TestSingleton::assert<int>(event.time, 1, "NOT gate event time");
  TestSingleton::assert<ll>(event.label, 1, "NOT gate event label");
}

void test_latch() {
  TestSingleton::start("latch");
  auto pins = make_test_pins({1, 0, 0, 0}); // Inputs: SET=1, RESET=0, INNER=0, OUT=0
  levents<int, int> events;
  
  EXAMPLE_GATES[2].solver(span<pin<int>>{&pins, 0, 4}, events, 0); // LATCH gate
  
  TestSingleton::assert<int>(pins[2].state, 1, "LATCH gate inner state");
  TestSingleton::assert<int>(pins[3].state, 1, "LATCH gate output state");
  TestSingleton::assert<int>(events.size(), 1, "LATCH gate event count");
  
  auto event = events.top();
  TestSingleton::assert<int>(event.signal, 1, "LATCH gate event signal");
  TestSingleton::assert<int>(event.time, 2, "LATCH gate event time");
  TestSingleton::assert<ll>(event.label, 2, "LATCH gate event label");
}

int gate_test() {
  
  test_and();
  test_or();
  test_latch();

  return TestSingleton::status("gate test");
}