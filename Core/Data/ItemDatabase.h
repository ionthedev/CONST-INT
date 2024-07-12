//
// Created by ion on 7/6/24.
//

#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <Core/Data/Item.h>

using namespace godot;

class ItemDatabase : public Resource
{
    GDCLASS(ItemDatabase, Resource)


public:

    TypedArray<Item> get_items() const;
    void set_items(const TypedArray<Item>& new_items);
    Ref<Texture2D> get_icon(StringName itemID);

protected:
    static void _bind_methods();
    TypedArray<Item> items;
};



#endif //ITEMDATABASE_H
