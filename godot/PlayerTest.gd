extends Player

func _ready() -> void:
	self.ground_settings.update_walk_speed(2.0)
	self.juice_settings.breath_duration = 5.0
	self.make_step_ahead_ray()
