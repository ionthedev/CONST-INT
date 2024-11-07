#include "EngineLayer.h"
#include "godot_cpp/variant/dictionary.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/project_settings.hpp>


using namespace CI;
using namespace godot;

EngineLayer *EngineLayer::singleton = nullptr;

void EngineLayer::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("initialize_layer"), &EngineLayer::initialize_layer);
}

EngineLayer *EngineLayer::get_singleton()
{
	return singleton;
}

EngineLayer::EngineLayer()
{
	ERR_FAIL_COND(singleton != nullptr);
	singleton = this;
	UtilityFunctions::print("Hello CI Singleton!");
}

EngineLayer::~EngineLayer()
{
	ERR_FAIL_COND(singleton != this);
	singleton = nullptr;
}

void EngineLayer::initialize_layer()
{
    UtilityFunctions::print("Hello CI Singleton!");
    ProjectSettings *project_settings = ProjectSettings::get_singleton();

    project_settings->set_setting("my_extension/custom_setting", Dictionary());
    project_settings->set_initial_value("my_extension/custom_setting", Dictionary());

    Dictionary property_info_1;
    property_info_1["name"] = "my_extension/custom_setting";
    property_info_1["type"] = Variant::INT;
    property_info_1["hint"] = PROPERTY_HINT_RANGE;
    property_info_1["hint_string"] = "0,1000,1";

    project_settings->add_property_info(property_info_1);

    // You can add more settings as needed
    project_settings->set_setting("my_extension/another_setting", Variant("Default Value"));
    project_settings->set_initial_value("my_extension/another_setting", Variant("Default Value"));
    Dictionary property_info_2;
    property_info_2["name"] = "my_extension/another_setting";
    property_info_2["type"] = Variant::STRING;
    project_settings->add_property_info(property_info_2);
}
