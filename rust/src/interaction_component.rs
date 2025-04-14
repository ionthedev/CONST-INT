use godot::classes::Node;
use godot::prelude::*;

#[derive(GodotClass)]
#[class(tool, base=Node)]
pub struct InteractionComponent {
    base: Base<Node>,
    parent_node: Option<Gd<Node>>,
}

#[godot_api]
impl INode for InteractionComponent {
    fn init(base: Base<Node>) -> Self {
        godot_print!("[CONST-INT] Interaction Component added to scene");
        Self {
            base,
            parent_node: None,
        }
    }

    fn ready(&mut self) {
        self.parent_node = self.base().get_parent();
        if let Some(parent) = &self.parent_node {
            self.connect_parent_signals();
        }
    }
}

#[godot_api]
impl InteractionComponent {
    #[signal]
    fn looked_at();

    #[signal]
    fn looked_away();

    #[signal]
    fn interacted();

    #[func]
    fn connect_parent_signals(&mut self) {
        // Create a mutable clone of the parent_node Option
        if let Some(mut parent) = self.parent_node.clone() {
            // Add user signals to the parent
            parent.add_user_signal("looked_at");
            parent.add_user_signal("looked_away");
            parent.add_user_signal("Interacted");

            // Get a reference to self as a node
            let this = unsafe { self.base().get_node_as::<Node>(".") };

            // Create callables using the Node reference
            let in_range_callable = Callable::from_object_method(&this, "in_range");
            let out_range_callable = Callable::from_object_method(&this, "out_range");
            let interacted_callable = Callable::from_object_method(&this, "interacted");

            // Connect the signals
            parent.connect("looked_at", &in_range_callable);
            parent.connect("looked_away", &out_range_callable);
            parent.connect("Interacted", &interacted_callable);
        }
    }

    #[func]
    fn in_range(&mut self) {
        godot_print!("In range");
        // Clone parent before calling methods
        if let Some(parent) = &self.parent_node {
            let mut parent_clone = parent.clone();
            if parent_clone.has_method("OnLookedAt") {
                parent_clone.call("OnLookedAt", &[]);
            }
        }
    }

    #[func]
    fn out_range(&mut self) {
        godot_print!("Out range");
        // Clone parent before calling methods
        if let Some(parent) = &self.parent_node {
            let mut parent_clone = parent.clone();
            if parent_clone.has_method("OnLookedAway") {
                parent_clone.call("OnLookedAway", &[]);
            }
        }
    }

    #[func]
    fn interacted(&mut self) {
        godot_print!("Interacted with");
        // Clone parent before calling methods
        if let Some(parent) = &self.parent_node {
            let mut parent_clone = parent.clone();
            if parent_clone.has_method("OnInteracted") {
                parent_clone.call("OnInteracted", &[]);
            }
        }
    }
}
