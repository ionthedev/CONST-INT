//
// Created by ion on 7/6/24.
//

#ifndef INVENTORYDATA_H
#define INVENTORYDATA_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/texture_rect.hpp>

using namespace godot;

class InventoryData : public Object {
    //TODO: Create data structure to store item id and position
    GDCLASS(InventoryData, Object)

protected:
    static void _bind_methods();

};



#endif //INVENTORYDATA_H
