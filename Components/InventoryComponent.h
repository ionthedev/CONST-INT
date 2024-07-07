//
// Created by ion on 7/6/24.
//

#ifndef INVENTORYCOMPONENT_H
#define INVENTORYCOMPONENT_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/texture_rect.hpp>

//TODO: Add boilerplate for Use, Inspect, Combine and Drop functionality.


using namespace godot;

class InventoryComponent : public Control {
    GDCLASS(InventoryComponent, Control)


public:

    void _ready() override;

protected:
    static void _bind_methods();

    void SetInventorySize(Vector2 _value);
    Vector2 GetInventorySize();

    void DrawGrid();
    TextureRect *GridSlotFactory();

    void _on_slot_mouse_entered(TextureRect *slot);
    void _on_slot_mouse_exited(TextureRect *slot);

    GridContainer *inventoryGrid = nullptr;

    void KillAllChildren();


    void SetSlotBaseColor(Color _value);
    Color GetSlotBaseColor();

    void SetSlotHoveredColor(Color _value);
    Color GetSlotHoveredColor();

private:
    Vector2 *inventorySize = new Vector2( 7, 4);


    Color slotBaseColor = Color::hex(0xffffffff);
    Color slotHoveredColor = Color::hex(0x88888888);

};



#endif //INVENTORYCOMPONENT_H
