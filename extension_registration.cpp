#include <gdextension_interface.h>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "Actors/Player.h"
#include "Components/InteractionComponent.h"
#include "Core/ComponentNode.h"
#include "Core/InputHandler.h"


using namespace godot;

void initializer(const ModuleInitializationLevel level) {
  if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }

  ClassDB::register_class<Player>();
  ClassDB::register_class<ActorSettings>();
  ClassDB::register_class<InteractionComponent>();
  ClassDB::register_class<InputHandler>();
}

void terminator(ModuleInitializationLevel level) {}

extern "C" {
  GDExtensionBool entrypoint(
    const GDExtensionInterfaceGetProcAddress get_proc_address,
    const GDExtensionClassLibraryPtr library,
    GDExtensionInitialization* initialization
  ) {
    const GDExtensionBinding::InitObject init_obj(get_proc_address, library, initialization);

    init_obj.register_initializer(initializer);
    init_obj.register_terminator(terminator);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
  }
}
