//
// Created by ion on 7/7/24.
//

#include "Item.h"

void Item::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("getItemID"), &Item::getItemID);
    ClassDB::bind_method(D_METHOD("setItemID", "_id"), &Item::setItemID);
    ClassDB::add_property("Item", PropertyInfo(Variant::STRING_NAME, "Item ID"), "setItemID", "getItemID");

    ClassDB::bind_method(D_METHOD("getItemIcon"), &Item::getItemIcon);
    ClassDB::bind_method(D_METHOD("setItemIcon", "_icon"), &Item::setItemIcon);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ItemIcon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "setItemIcon", "getItemIcon");

}

void Item::setItemID(StringName _id)
{
    itemID = _id;
}

StringName Item::getItemID()
{
    return itemID;
}

void Item::setItemMaxStack(int _amount)
{
    itemMaxStack = _amount;
}

int Item::getItemMaxStack()
{
    return itemMaxStack;
}

void Item::setItemIcon(Ref<Texture2D>  _icon)
{
    itemIcon = _icon;
}

Ref<Texture2D>  Item::getItemIcon()
{
    return itemIcon;
}

bool Item::canItemStack()
{
    if(itemMaxStack > 1) return true;
    return false;
}

void Item::copy_from(const Item& other)
{
    // Copy all relevant data members from 'other' to 'this'
    this->itemIcon = other.itemIcon;
    this->itemMaxStack = other.itemMaxStack;
    this->itemID = other.itemID;
    // Add other necessary member variables here
}
