#include <string>

#include "test_definitions.h"

#include "collections_test/llabeling_test.h"

#include "collections/llabeling.h"

int llabeling_test() {
  //run all declared tests

  test_add();
  test_set();
  test_get();
  test_remove();
  test_add_remove_add();

  return TestSingleton::status("llabeling test");
}

void test_add() {
  TestSingleton::start("add");
  Labeling<std::string> labels;
  
  labels.add("example");
  labels.add("test");

  TestSingleton::assert<int>(labels.size(), 2, "size");
}

void test_set() {
  TestSingleton::start("set");
  Labeling<std::string> labels;
  
  labels.set("example", 2);

  TestSingleton::assert<int>(labels.size(), 3, "size");
  std::string* val = labels.get(2);
  TestSingleton::assert<bool>(val != nullptr && *val == "example", true, "value at position 2");
}

void test_get() {
  TestSingleton::start("get");
  Labeling<std::string> labels;
  
  labels.set("example", 1);

  std::string* val1 = labels.get(1);
  TestSingleton::assert<bool>(val1 != nullptr && *val1 == "example", true, "value at position 1");
  
  std::string* val0 = labels.get(0);
  TestSingleton::assert<bool>(val0 == nullptr, true, "nil at position 0");
}

void test_remove() {
  TestSingleton::start("remove");
  Labeling<std::string> labels;
  
  labels.set("example", 1);
  labels.remove(1);

  std::string* val = labels.get(1);
  TestSingleton::assert<bool>(val == nullptr, true, "nil at position 1 after removal");
}

void test_add_remove_add() {
  TestSingleton::start("add remove add");
  Labeling<std::string> labels;
  
  ll first_label = labels.add("first");
  ll second_label = labels.add("second");
  
  labels.remove(second_label);
  
  ll third_label = labels.add("third");
  
  TestSingleton::assert<bool>(third_label == second_label, true, "new element should reuse removed index");
  std::string* val = labels.get(third_label);
  TestSingleton::assert<bool>(val != nullptr && *val == "third", true, "value at reused index should be 'third'");
}
