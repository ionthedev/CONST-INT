//
// Created by Brandon Friend on 9/21/24.
//

#ifndef ASTAR3DGRID_H
#define ASTAR3DGRID_H


#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/visual_instance3d.hpp>
#include <godot_cpp/variant/vector3.hpp>



using namespace godot;

struct AStar3DGridPoint
{
    long *point_id;
    Vector3 *position;
};

class AStar3DGridData : public Resource {
    GDCLASS(AStar3DGridData, Resource);

    RID point;

    void _set_data(const Vector<AStar3DGridPoint> &p_data);
    Vector<AStar3DGridPoint> _get_data() const;
    Vector<AStar3DGridPoint> points;
};

class AStar3DGrid : VisualInstance3D {

public:
    enum Subdiv {
        SUBDIV_64,
        SUBDIV_128,
        SUBDIV_256,
        SUBDIV_512,
        SUBDIV_MAX

    };

    typedef void (*BakeBeginFunc)(int);
    typedef void (*BakeStepFunc)(int, const String &);
    typedef void (*BakeEndFunc)();

    static BakeBeginFunc bake_begin_function;
    static BakeStepFunc bake_step_function;
    static BakeEndFunc bake_end_function;

    void set_grid_data(const Ref<AStar3DGridData> &p_data);
    Ref<AStar3DGridData> get_grid_data() const;

    void set_subdiv(Subdiv p_subdiv);
    Subdiv get_subdiv() const;

    void set_size(const Vector3 &p_size);
    Vector3 get_size() const;

    Vector3i get_estimated_cell_size() const;

    void bake(Node *p_from_node = nullptr, bool p_create_visual_debug = false);

    virtual AABB _get_aabb() const override;

    PackedStringArray _get_configuration_warnings() const override;

    AStar3DGrid();
    ~AStar3DGrid();

private:
    Ref<AStar3DGridData> grid_data;

    RID astar3dgrid;
    Subdiv subdiv = SUBDIV_128;

    Vector3 size = Vector3(20, 20, 20);

protected:
    static void _bind_methods();


};

VARIANT_ENUM_CAST(AStar3DGrid::Subdiv)
#endif //ASTAR3DGRID_H
