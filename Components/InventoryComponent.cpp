//
// Created by ion on 7/6/24.
//

#include "InventoryComponent.h"

#include <godot_cpp/variant/utility_functions.hpp>

#include "Core/Data/ItemDatabase.h"

void InventoryComponent::_ready()
{
    SetInventorySize(Vector2(8, 4));
    DisplayItems();
}

void InventoryComponent::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("GetInventorySize"), &InventoryComponent::GetInventorySize);
    ClassDB::bind_method(D_METHOD("SetInventorySize", "_value"), &InventoryComponent::SetInventorySize);
    ClassDB::add_property("InventoryComponent", PropertyInfo(Variant::VECTOR2, "_value"), "SetInventorySize", "GetInventorySize");

    ClassDB::bind_method(D_METHOD("_on_slot_mouse_entered", "slot"), &InventoryComponent::_on_slot_mouse_entered);
    ClassDB::bind_method(D_METHOD("_on_slot_mouse_exited", "slot"), &InventoryComponent::_on_slot_mouse_exited);

    ClassDB::bind_method(D_METHOD("GetSlotBaseColor"), &InventoryComponent::GetSlotBaseColor);
    ClassDB::bind_method(D_METHOD("SetSlotBaseColor", "_value"), &InventoryComponent::SetSlotBaseColor);
    ClassDB::add_property("InventoryComponent", PropertyInfo(Variant::COLOR, "Slot Base Color"), "SetSlotBaseColor", "GetSlotBaseColor");

    ClassDB::bind_method(D_METHOD("GetSlotHoveredColor"), &InventoryComponent::GetSlotHoveredColor);
    ClassDB::bind_method(D_METHOD("SetSlotHoveredColor", "_value"), &InventoryComponent::SetSlotHoveredColor);
    ClassDB::add_property("InventoryComponent", PropertyInfo(Variant::COLOR, "Slot Hover Color"), "SetSlotHoveredColor", "GetSlotHoveredColor");

    ClassDB::bind_method(D_METHOD("set_items", "new_items"), &InventoryComponent::set_items);
    ClassDB::bind_method(D_METHOD("get_items"), &InventoryComponent::get_items);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "Items", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::STRING_NAME, PROPERTY_HINT_TYPE_STRING, "InventoryObject")), "set_items", "get_items");

    ClassDB::bind_method(D_METHOD("set_database", "database"), &InventoryComponent::set_database);
    ClassDB::bind_method(D_METHOD("get_database"), &InventoryComponent::get_database);
    ClassDB::add_property("InventoryComponent", PropertyInfo(Variant::OBJECT, "database", PROPERTY_HINT_RESOURCE_TYPE, "ItemDatabase"), "set_database", "get_database");

}

void InventoryComponent::SetInventorySize(Vector2 _value)
{
    Vector2 cachedSize = *inventorySize;
    if(_value.x > 0 && _value.y > 0)
    {
        *inventorySize = _value;
    }
    else
    {
        *inventorySize = cachedSize;
    }
    cachedSize = Vector2(0,0);
    KillAllChildren();
    DrawGrid();
}

Vector2 InventoryComponent::GetInventorySize()
{
    return *inventorySize;
}

void InventoryComponent::DrawGrid()
{
    int width = GetInventorySize().x;
    int height = GetInventorySize().y;
    Vector2i gridSize = (GetInventorySize()*62) + Vector2(2,2);
    int slotIndex = 0;
    set_size(gridSize);
    inventoryGrid = memnew(GridContainer);
    inventoryGrid->add_theme_constant_override("h_separation", -2);
    inventoryGrid->add_theme_constant_override("v_separation", -2);
    add_child(inventoryGrid);

    if(GetInventorySize() != Vector2(0,0))
    {

        inventoryGrid->set_columns(width);
        for(int column = 0; column < width; column++)
        {
            for(int row = 0; row < height; row++)
            {
                //Create ColorRect from Factory
                auto slot = GridSlotFactory();
                slot->set_name(String("Slot_") + String::num_int64(slotIndex+1));
                inventoryGrid->add_child(slot, true);

                slot->connect("mouse_entered", Callable(this, "_on_slot_mouse_entered").bind(slot));
                slot->connect("mouse_exited", Callable(this, "_on_slot_mouse_exited").bind(slot));
                slotIndex++;
            }
        }
    }



}

TextureRect *InventoryComponent::GridSlotFactory()
{
    Ref<Resource> gridTexture = memnew(Resource);
    gridTexture = ResourceLoader::get_singleton()->load("res://bin/CONST-INT/UI/Inventory/GridSlot.png");
    TextureRect *slot = memnew(TextureRect);
    slot->set_texture(gridTexture);
    slot->set_custom_minimum_size(Vector2(CellSize, CellSize));
    return slot;
}

void InventoryComponent::_on_slot_mouse_entered(TextureRect *slot)
{
    slot->set_modulate(slotHoveredColor);
    UtilityFunctions::print(slot->get_name());
}

void InventoryComponent::_on_slot_mouse_exited(TextureRect *slot)
{
    slot->set_modulate(slotBaseColor);
}


void InventoryComponent::KillAllChildren()
{
    if(inventoryGrid == nullptr) return;
    int childCount = inventoryGrid->get_child_count();
    if(childCount == 0) return;

    for(int child = 0; child < childCount; child++)
    {
        inventoryGrid->get_child(child)->queue_free();
    }
    inventoryGrid->queue_free();
}

void InventoryComponent::SetSlotBaseColor(Color _value)
{
    slotBaseColor = _value;
}

Color InventoryComponent::GetSlotBaseColor()
{
    return slotBaseColor;
}

void InventoryComponent::SetSlotHoveredColor(Color _value)
{
    slotHoveredColor = _value;
}

Color InventoryComponent::GetSlotHoveredColor()
{
    return slotHoveredColor;
}

void InventoryComponent::GiveItem(InventoryObject *_item)
{

}

void InventoryComponent::DisplayItems()
{
    for(int i = 0; i < items.size(); i++)
    {
        InventoryObject *itemObject = memnew(InventoryObject);
        itemObject->set_texture(database->get_icon(items[i]));
        itemObject->set_custom_minimum_size(itemObject->get_texture()->get_size()*2);
        add_child(itemObject);
        itemObject->set_position(Vector2(0, 0));
    }

}

void InventoryComponent::MakeAxe()
{

}

TypedArray<StringName> InventoryComponent::get_items() const
{
    TypedArray<StringName> items_;
    for (int i = 0; i < items.size(); ++i) {
        items_.push_back(items[i]);
    }
    return items_;
}

void InventoryComponent::set_items(const TypedArray<StringName>& new_items)
{
    items.clear();
    for (int i = 0; i < new_items.size(); ++i) {
        items.insert(i, new_items[i]);
    }
}

void InventoryComponent::set_database(Ref<ItemDatabase> new_database)
{
    database = new_database;
}

Ref<ItemDatabase> InventoryComponent::get_database()
{
    return database;
}






