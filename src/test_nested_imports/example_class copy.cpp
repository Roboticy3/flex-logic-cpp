
#include <godot_cpp/godot.hpp>

#include "example_class copy.h"

void ExampleClass2::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &ExampleClass2::print_type);
}

void ExampleClass2::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}
