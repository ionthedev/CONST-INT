extends StaticBody3D  # Change to match your object type

@onready var mesh = $MeshInstance3D  # Assuming you have a mesh
var original_material = null
var highlight_material = null

func _ready():
	# Store the original material
	if mesh and mesh.get_surface_override_material(0):
		original_material = mesh.get_surface_override_material(0)
		
		# Create a highlighted version of the material
		highlight_material = original_material.duplicate()
		highlight_material.albedo_color = Color(8.5, 1.5, 0.3, 1.0)
	
	# Debug output
	print("Setting up interactable: ", name)
	print("Signals available: ", get_signal_list())
	

# These methods will be called by your InteractionComponent
func OnLookedAt():
	print(name, " is now being looked at")
	if mesh and highlight_material:
		mesh.set_surface_override_material(0, highlight_material)

func OnLookedAway():
	print(name, " is no longer being looked at")
	if mesh and original_material:
		mesh.set_surface_override_material(0, original_material)

func OnInteracted():
	print(name, " was interacted with!")
	# Do something when interacted with
	var tween = create_tween()
	tween.tween_property(self, "scale", Vector3(1.2, 1.2, 1.2), 0.1)
	tween.tween_property(self, "scale", Vector3(1.0, 1.0, 1.0), 0.1)
