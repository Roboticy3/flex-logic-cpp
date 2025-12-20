#pragma once

#include <string>

#include <godot_cpp/core/print_string.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/variant.hpp>

using namespace godot;

class TestSingleton {
  
  inline static long long t_state = 0;

  public:
    inline static void start(std::string name) { 
      print_line(vformat("Starting test %s...", name.c_str()));

    }
    
    template<typename T>
    inline static void assert(T value, T compare, std::string label) {
      if ((value != compare)) {
        TestSingleton::t_state |= (long long)(value != compare);
        print_line(vformat("\tASSERTION %s FAILED! (expected %s, found %s)", label.c_str(), compare, value)); 
      }
    } 

    inline static void fail(std::string msg) {
      TestSingleton::t_state |= 1;
      print_line(vformat("%s", msg.c_str()));
    }

    inline static long long status(std::string name) { 
      print_line(vformat("Test status for %s... %s", name.c_str(), TestSingleton::t_state ? "NOT OK":"OK"));
      return TestSingleton::t_state;
    }
};

