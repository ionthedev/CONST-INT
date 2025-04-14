extends Area3D

@export var stats: StatComponent
@export var change_value: float

func _on_area_3d_body_entered(body: Node3D) -> void:
	if body.is_in_group("Player"):
		stats.modify_stat_value("Health", change_value)
