//
// Created by ion on 7/10/24.
//

#ifndef INVENTORYOBJECT_H
#define INVENTORYOBJECT_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include "Item.h"

using namespace godot;

class InventoryObject : public TextureRect {
    GDCLASS(InventoryObject, TextureRect)

public:


protected:
    static void _bind_methods();
    void setItemID(const StringName& p_itemID);
    [[nodiscard]] StringName getItemID() const;

private:
    StringName itemID;
};

#endif //InventoryObject_H
