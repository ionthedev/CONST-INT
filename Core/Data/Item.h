//
// Created by ion on 7/7/24.
//

#ifndef ITEM_H
#define ITEM_H
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class Item : public Resource {
    GDCLASS(Item, Resource)

public:
    void setItemID(StringName _id);
    StringName getItemID();

    void setItemMaxStack(int _amount);
    int getItemMaxStack();

    void setItemIcon(Ref<Texture2D>  _icon);
    Ref<Texture2D>  getItemIcon();

    bool canItemStack();
    void copy_from(const Item &other);


protected:
    static void _bind_methods();







private:
    StringName itemID;
    int itemMaxStack = 1;
    Ref<Texture2D> itemIcon;
};



#endif //ITEM_H
