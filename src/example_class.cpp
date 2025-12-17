#include "example_class.h"
#include "test_nested_imports/example_class copy.h"

void ExampleClass::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &ExampleClass::print_type);
}

void ExampleClass::print_type(const Variant &p_variant) const {
	ExampleClass2 *example = memnew(ExampleClass2);
	example->print_type(p_variant);
}
