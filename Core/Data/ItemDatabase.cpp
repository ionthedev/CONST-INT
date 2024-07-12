//
// Created by ion on 7/6/24.
//

#include "ItemDatabase.h"


TypedArray<Item> ItemDatabase::get_items() const
{
    TypedArray<Item> items_;
    for (int i = 0; i < items.size(); ++i) {
        items_.push_back(items[i]);
    }
    return items_;
}

void ItemDatabase::set_items(const TypedArray<Item>& new_items)
{
    items.clear();
    for (int i = 0; i < new_items.size(); ++i) {
        items.insert(i, new_items[i]);
    }
}

Ref<Texture2D> ItemDatabase::get_icon(StringName itemID)
{
    for (int i = 0; i < items.size(); ++i)
    {
        Item *curr_item = cast_to<Item>(items[i]);
        if(curr_item->getItemID() == itemID) return curr_item->getItemIcon();
    }
    return nullptr;
}

void ItemDatabase::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_items", "new_items"), &ItemDatabase::set_items);
    ClassDB::bind_method(D_METHOD("get_items"), &ItemDatabase::get_items);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "Items", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Item")), "set_items", "get_items");
}
