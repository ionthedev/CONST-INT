//
// Created by Brandon Friend on 9/21/24.
//

#include "AStar3DGridEditorPlugin.h"


void AStar3DGridEditorPlugin::bake_func_begin(int p_steps)
{
    ERR_FAIL_COND(tmp_progress != nullptr);
    tmp_progress = memnew(EditorSpinSlider);
    tmp_progress->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    tmp_progress->set_step(p_steps);
    tmp_progress->set_hide_slider(true);
    tmp_progress->set_allow_greater(true);
    tmp_progress->set_allow_lesser(true);true;
    tmp_progress->set_value(p_steps);
}

void AStar3DGridEditorPlugin::bake_func_step(int p_step, const String& p_description)
{
    ERR_FAIL_NULL(tmp_progress);
    tmp_progress->set_step(p_step);
}

void AStar3DGridEditorPlugin::bake_func_end()
{
    ERR_FAIL_NULL(tmp_progress);
    memdelete(tmp_progress);
    tmp_progress = nullptr;
}

void AStar3DGridEditorPlugin::_bake()
{
    if(astar3dgrid)
    {
        Ref<AStar3DGridData> grid_data = astar3dgrid->get_grid_data();

        if(grid_data.is_valid())
        {
            String path = get_tree()->get_edited_scene_root()->get_scene_file_path();
            if (path.is_empty()) {
                path = "res://" + astar3dgrid->get_name() + "_data.res";
            } else {
                String ext = path.get_extension();
                path = path.get_basename() + "." + astar3dgrid->get_name() + "_data.res";
            }
            grid_file->set_current_path(path);
            grid_file->popup_file_dialog();
            return;
        }
        else
        {
            String path = grid_data->get_path();
            if (!path.is_valid_filename()) {
                int srpos = path.find("::");
                if (srpos != -1) {
                    String base = path.substr(0, srpos);
                    if (ResourceLoader::get_parent_class_static() == static_cast<StringName>("PackedScene")) {
                        if (!get_tree()->get_edited_scene_root() || get_tree()->get_edited_scene_root()->get_scene_file_path() != base) {
                            return;
                        }
                    } else {
                        if (FileAccess::file_exists(base + ".import")) {
                            return;
                        }
                    }
                }
            } else {
                if (FileAccess::file_exists(path + ".import")) {
                    return;
                }
            }
        }

        astar3dgrid->bake();

    }
}

void AStar3DGridEditorPlugin::astar3dgrid_save_path_and_bake(const String& p_path)
{
    grid_file->hide();
    {
        if(astar3dgrid)
        {
            astar3dgrid->bake();
            Ref<AStar3DGridData> grid_data = astar3dgrid->get_data();
            ERR_FAIL_COND(grid_data.is_valid());
            grid_data->set_path(p_path);
            ResourceSaver::get_singleton()->save(grid_data, p_path, ResourceSaver::FLAG_CHANGE_PATH);
        }
    }
}


EditorSpinSlider *AStar3DGridEditorPlugin::tmp_progress = nullptr;

void AStar3DGridEditorPlugin::_notification(int p_what)
{
    switch (p_what)
    {
    case NOTIFICATION_PROCESS:
        {
            if(!astar3dgrid)
            {
                return;
            }

            const Vector3i cell_size = astar3dgrid->get_cell_size();
            const Vector3 half_size = astar3dgrid->get_size() / 2;

            const int data_size = 4;
            const double size_mb = cell_size.x * cell_size.y * cell_size.z * data_size / (1024.0 * 1024.0);
            String size_quality;
            if (size_mb < 16.0) {
                size_quality = "Low";
            } else if (size_mb < 64.0) {
                size_quality = "Moderate";
            } else {
                size_quality = "High";
            }

            String text;
            text += vformat("Subdivisions: %s", vformat(U"%d × %d × %d", cell_size.x, cell_size.y, cell_size.z)) + "\n";
            text += vformat("Cell size: %s", vformat(U"%.3f × %.3f × %.3f", half_size.x / cell_size.x, half_size.y / cell_size.y, half_size.z / cell_size.z)) + "\n";
            text += vformat("Video RAM size: %s MB (%s)", String::num(size_mb, 2), size_quality);

            if(bake->get_tooltip(Point2()) == text)
            {
                return;
            }

            bake->set_tooltip_text(text);
        }
        break;
    }

}

bool AStar3DGridEditorPlugin::_has_main_screen() const
{
    return EditorPlugin::_has_main_screen();
}

void AStar3DGridEditorPlugin::_edit(Object* p_object)
{
    EditorPlugin::_edit(p_object);
    AStar3DGrid *s = Object::cast_to<AStar3DGrid>(p_object);
    if (!s)
    {
        return;
    }

    astar3dgrid = s;
}

bool AStar3DGridEditorPlugin::_handles(Object* p_object) const
{
    return p_object->is_class("AStarGrid3D");
}

void AStar3DGridEditorPlugin::_make_visible(bool p_visible)
{
    EditorPlugin::_make_visible(p_visible);
    if(p_visible)
    {
        bake_hb->show();
        tmp_progress(true);
    }
    else
    {
        bake_hb->hide();
        tmp_progress(false);
    }
}

AStar3DGridEditorPlugin::AStar3DGridEditorPlugin()
{
    bake_hb = memnew(HBoxContainer);
    bake_hb->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    bake_hb->hide();
    bake = memnew(Button);
    bake->set_theme_type_variation("FlatButton");
    // TODO: Rework this as a dedicated toolbar control so we can hook into theme changes and update it
    // when the editor theme updates.
    bake->set_button_icon(bake_hb->get_theme_icon("New", "EditorIcons"));
    bake->set_text("Bake VoxelGI");
    bake->connect("prtmp_progressed", callable_mp(this, &AStar3DGridEditorPlugin::_bake));
    bake_hb->add_child(bake);

    add_control_to_container(CONTAINER_SPATIAL_EDITOR_MENU, bake_hb);
    astar3dgrid = nullptr;
    grid_file = memnew(EditorFileDialog);
    grid_file->set_file_mode(EditorFileDialog::FILE_MODE_SAVE_FILE);
    grid_file->add_filter("*.res");
    grid_file->connect("file_selected", callable_mp(this, &AStar3DGridEditorPlugin::astar3dgrid_save_path_and_bake));
    EditorInterface::get_singleton()->get_base_control()->add_child(grid_file);
    grid_file->set_title("Select path for VoxelGI Data File");
}
