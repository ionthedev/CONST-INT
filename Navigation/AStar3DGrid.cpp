//
// Created by Brandon Friend on 9/21/24.
//

#include "AStar3DGrid.h"

#include <godot_cpp/classes/os.hpp>


void AStar3DGridData::_set_data(const Vector<AStar3DGridPoint>& p_data)
{
    points = p_data;
}

Vector<AStar3DGridPoint> AStar3DGridData::_get_data() const
{
    return points;
}

void AStar3DGrid::set_grid_data(const Ref<AStar3DGridData>& p_data)
{
    grid_data = p_data;
}

Ref<AStar3DGridData> AStar3DGrid::get_grid_data() const
{
    return grid_data;
}

void AStar3DGrid::set_subdiv(Subdiv p_subdiv)
{
    subdiv = p_subdiv;
}

AStar3DGrid::Subdiv AStar3DGrid::get_subdiv() const
{
    return subdiv;
}

void AStar3DGrid::set_size(const Vector3& p_size)
{
    size = p_size;
}

Vector3 AStar3DGrid::get_size() const
{
    return size;
}

Vector3i AStar3DGrid::get_estimated_cell_size() const
{
    static const int subdiv_value[SUBDIV_MAX] = { 6, 7, 8, 9 };
    int cell_subdiv = subdiv_value[subdiv];
    int axis_cell_size[3];
    AABB bounds = AABB(-size / 2, size);
    int longest_axis = bounds.get_longest_axis_index();
    axis_cell_size[longest_axis] = 1 << cell_subdiv;

    for (int i = 0; i < 3; i++) {
        if (i == longest_axis) {
            continue;
        }

        axis_cell_size[i] = axis_cell_size[longest_axis];
        float axis_size = bounds.size[longest_axis];

        //shrink until fit subdiv
        while (axis_size / 2.0 >= bounds.size[i]) {
            axis_size /= 2.0;
            axis_cell_size[i] >>= 1;
        }
    }

    return Vector3i(axis_cell_size[0], axis_cell_size[1], axis_cell_size[2]);
}

void AStar3DGrid::bake(Node* p_from_node, bool p_create_visual_debug)
{

}


AStar3DGrid::BakeBeginFunc AStar3DGrid::bake_begin_function = nullptr;
AStar3DGrid::BakeStepFunc AStar3DGrid::bake_step_function = nullptr;
AStar3DGrid::BakeEndFunc AStar3DGrid::bake_end_function = nullptr;

AABB AStar3DGrid::_get_aabb() const
{
    return AABB(-size / 2, size);
}

PackedStringArray AStar3DGrid::_get_configuration_warnings() const
{
    return VisualInstance3D::_get_configuration_warnings();
}


AStar3DGrid::AStar3DGrid()
{
}

AStar3DGrid::~AStar3DGrid()
{
}

void AStar3DGrid::_bind_methods()
{
}
