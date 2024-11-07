#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "my_node.hpp"
#include "my_singleton.hpp"
#include "Core/EngineLayer.h"

using namespace godot;
using namespace CI;
static MySingleton *_my_singleton;
static EngineLayer *_engine_layer;

void gdextension_initialize(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		ClassDB::register_class<MyNode>();
		ClassDB::register_class<MySingleton>();

		_my_singleton = memnew(MySingleton);
		Engine::get_singleton()->register_singleton("MySingleton", MySingleton::get_singleton());

	}

	#ifdef TOOLS_ENABLED
		if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
            ClassDB::register_internal_class<EngineLayer>();
            _engine_layer = memnew(EngineLayer);
            Engine::get_singleton()->register_singleton("EngineLayer", EngineLayer::get_singleton());

		}
	#endif // TOOLS_ENABLED
}

void gdextension_terminate(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		Engine::get_singleton()->unregister_singleton("MySingleton");
		memdelete(_my_singleton);
	}
	#ifdef TOOLS_ENABLED
	if (p_level == godot::MODULE_INITIALIZATION_LEVEL_EDITOR)
	{
    	Engine::get_singleton()->unregister_singleton("EngineLayer");
    	memdelete(_engine_layer);
	}
	#endif // TOOLS_ENABLED
}

extern "C"
{
	GDExtensionBool GDE_EXPORT entrypoint(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(gdextension_initialize);
		init_obj.register_terminator(gdextension_terminate);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
