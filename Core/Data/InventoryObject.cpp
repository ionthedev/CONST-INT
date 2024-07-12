#include "InventoryObject.h"
#include <godot_cpp/variant/utility_functions.hpp>

void InventoryObject::_bind_methods()
{
}

void InventoryObject::setItemID(const StringName& p_itemID)
{
    itemID = p_itemID;
}

StringName InventoryObject::getItemID() const
{
    return itemID;
}
