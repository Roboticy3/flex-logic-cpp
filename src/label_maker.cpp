
#include <sstream>
#include <stdexcept>
#include <cctype>

#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/core/print_string.hpp>
#include <godot_cpp/variant/string.hpp>

#include "label_maker.h"

using namespace godot;

void LabelMaker::_bind_methods() {
  ClassDB::bind_method(D_METHOD("label", "int"), &LabelMaker::label);
  ClassDB::bind_method(D_METHOD("index", "String"), &LabelMaker::index);
}

String LabelMaker::label(int of) {
  if (of < 0) {
    std::string oops = "A";
    return String(oops.c_str());
  }

  std::string result;
  
  while (of >= 0) {
    char digit = of % base;
    std::string prepend = " ";
    prepend[0] = digit + offset;

    result = prepend + result;
    
    of = of / base - 1;
  }

  return String(result.c_str());
}

int LabelMaker::index(String of) {
  if (of.is_empty()) return -1;

  int value = 0;
  int place = 1;
  for (int i = of.length() - 1; i >= 0; i--) {
    char32_t c = of[i];
    
    int after_digit = c - 'A' + 1;

    value += after_digit * place;

    place *= 26;
  }

  return value - 1; // shift back to 0-based
}