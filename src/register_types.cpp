#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "example_class.h"
#include "test_nested_imports/example_class copy.h"
#include "label_maker.h"

#include "collections/levents.h"
#include "collections/llabeling.h"

#include "collections_test/levents_test.h"
#include "collections_test/llabeling_test.h"

#include "test_definitions.h"

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	test_gdextension();

	GDREGISTER_CLASS(ExampleClass);
	GDREGISTER_CLASS(ExampleClass2);

	//GDREGISTER_CLASS(Labeling); Can't register template class directly :(
	GDREGISTER_CLASS(LabelMaker);
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

void test_gdextension() {
	TestSingleton::start("test gdextension");
	levents_test();
	llabeling_test();
	TestSingleton::status("all tests");
}

extern "C"
{
	// Initialization
	GDExtensionBool GDE_EXPORT flex_logic_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_gdextension_types);
		init_obj.register_terminator(uninitialize_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}