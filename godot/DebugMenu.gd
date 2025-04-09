extends Control

@export var InputDir: Label
@export var WishDir: Label
@export var currSpeed: Label
@export var velocity: Label
@export var _Player: Player

func _process(delta: float) -> void:
	InputDir.text = str(_Player.calc_input_dir())
	WishDir.text = str(_Player.calc_wish_dir())
	currSpeed.text = str(_Player.get_curr_speed())
	velocity.text = str(_Player.get_real_velocity())
