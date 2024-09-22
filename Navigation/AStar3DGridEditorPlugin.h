//
// Created by Brandon Friend on 9/21/24.
//

#ifndef ASTAR3DGRIDEDITORPLUGIN_H
#define ASTAR3DGRIDEDITORPLUGIN_H

#include "AStar3DGrid.h"
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/material.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/editor_file_dialog.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/editor_spin_slider.hpp>
#include <godot_cpp/classes/editor_node3d_gizmo.hpp>

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/resource_saver.hpp>
#include <godot_cpp/classes/scene_tree.hpp>



struct EditorProgress;

class AStar3DGridEditorPlugin : public EditorPlugin {
    GDCLASS(AStar3DGridEditorPlugin, EditorPlugin);

    AStar3DGrid *astar3dgrid = nullptr;
    HBoxContainer *bake_hb = nullptr;
    Button *bake = nullptr;

    EditorFileDialog *grid_file = nullptr;

    static EditorSpinSlider *tmp_progress;
    static void bake_func_begin(int p_steps);
    static void bake_func_step(int p_step, const String &p_description);
    static void bake_func_end();

    void _bake();
    void astar3dgrid_save_path_and_bake(const String& p_path);


protected:
    void _notification(int p_what);

public:
    String _get_plugin_name() const override { return "AStar3DGrid";}
    bool _has_main_screen() const override;
    void _edit(Object* p_object) override;
    bool _handles(Object *p_object) const override;
    void _make_visible(bool p_visible) override;

    AStar3DGridEditorPlugin();
    ~AStar3DGridEditorPlugin();

};



#endif //ASTAR3DGRIDEDITORPLUGIN_H
