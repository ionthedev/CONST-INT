//
// Created by ion on 6/21/24.
//

#ifndef INTERACTIONCOMPONENT_H
#define INTERACTIONCOMPONENT_H

#include <Core/ComponentNode.h>

using namespace godot;

class InteractionComponent : public ComponentNode {
    GDCLASS(InteractionComponent, ComponentNode)


public:

    void _ready() override;

protected:
    static void _bind_methods();

    Node *parent = nullptr;



    void connect_signals();

};



#endif //INTERACTIONCOMPONENT_H
