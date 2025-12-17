#include <string>

#include "test_definitions.h"

#include "collections_test/levents_test.h"

#include "collections/levents.h"

int levents_test() {
  //run all declared tests

  test_levents_with_int_time();
  test_levents_with_float_time();
  test_levents_with_string_state();

  return TestSingleton::status("levents test");
}

void test_levents_with_int_time() {
  TestSingleton::start("levents with int time");
  levents<int, int> events;

  levent<int, int> e[3] = {
    {5, 1, 1},
    {3, 1, 2},
    {8, 1, 3},
  };
  events.push(e[0]);
  events.push(e[1]);
  events.push(e[2]);

  TestSingleton::assert<int>(events.size(), 3, "size");
  
  levent<int, int> l1 = events.top();
  events.pop();
  TestSingleton::assert<int>(l1.time, 3, "time 1");

  levent<int, int> l2 = events.top();
  events.pop();
  TestSingleton::assert<int>(l2.time, 5, "time 2");

  levent<int, int> l3 = events.top();
  events.pop();
  TestSingleton::assert<int>(l3.time, 8, "time 3");
}

void test_levents_with_float_time() {
  TestSingleton::start("levents with float time");
  levents<int, double> events;

  levent<int, double> e[3] = {
    {5.5, 1, 1},
    {3.3, 1, 2},
    {8.8, 1, 3},
  };
  events.push(e[0]);
  events.push(e[1]);
  events.push(e[2]);

  TestSingleton::assert<int>(events.size(), 3, "size");
  
  levent<int, double> l1 = events.top();
  events.pop();
  TestSingleton::assert<double>(l1.time, 3.3, "time 1");

  levent<int, double> l2 = events.top();
  events.pop();
  TestSingleton::assert<double>(l2.time, 5.5, "time 2");

  levent<int, double> l3 = events.top();
  events.pop();
  TestSingleton::assert<double>(l3.time, 8.8, "time 3");
}

void test_levents_with_string_state() {
  TestSingleton::start("levents with string state");
  levents<std::string, int> events;

  levent<std::string, int> e[3] = {
    {10, "ON", 1},
    {2, "OFF", 2},
    {7, "Signal", 3},
  };
  events.push(e[0]);
  events.push(e[1]);
  events.push(e[2]);

  TestSingleton::assert<int>(events.size(), 3, "size");
  
  levent<std::string, int> l1 = events.top();
  events.pop();
  TestSingleton::assert<int>(l1.time, 2, "time 1");

  levent<std::string, int> l2 = events.top();
  events.pop();
  TestSingleton::assert<int>(l2.time, 7, "time 2");

  levent<std::string, int> l3 = events.top();
  events.pop();
  TestSingleton::assert<int>(l3.time, 10, "time 3");
}