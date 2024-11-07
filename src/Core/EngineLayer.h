#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
namespace CI {
class EngineLayer : public Object
{
	GDCLASS(EngineLayer, Object);

	static EngineLayer *singleton;

protected:
	static void _bind_methods();

public:
	static EngineLayer *get_singleton();

	EngineLayer();
	~EngineLayer();

	void initialize_layer();
};
}
