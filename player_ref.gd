extends CharacterBody3D
class_name Player

@export_category("Movement Variables")
@export var lookSensitivity : float = 0.006
@export var jumpVelocity := 6.0
@export var autoBhop := true
@export var walkSpeed := 7.0
@export var sprintSpeed := 8.5
@export var groundAccel := 14.0

@export var groundDeccel := 10.0
@export var groundFriction := 6.0
@export var climb_speed := 7.0

@export_category("Air Movement Variables")
@export var airCap := 0.05
@export var airAccel := 800.0
@export var airMoveSpeed := 500.0

@export_category("LeaningVariables")
@export var leanSpeed := 2.5
@export var leanAmount := -45.0
var is_leaning := false

@export_category("Footsteps")
@export var footstepPlayer: AudioStreamPlayer3D

@export_category("Crouching Variables")
var is_crouched := false
@export var crouchTranslate := 0.5
@export var crouchJumpAdd: float = crouchTranslate * 0.9
@export_category("Stair Stepping Variables")
@export var maxStepHeight := 0.5
@onready var stairsAheadRaycast3D : RayCast3D = $StairsAheadRaycast3D
@onready var stairsBelowRaycast3D : RayCast3D = $StairsBelowRaycast3D
var snappedToStairLastFrame := false
var lastFrameWasOnFloor := -INF


@export_category("Juice")
@export var headbobMoveAmount : float = 0.06
@export var headbobMoveFrequency : float = 2.46
@export var headbobTime : float = 0.0
@export var breathPosCurve : CurveXYZTexture
@export var breathRotCurve : CurveXYZTexture
@export var breathTime : float = 0.
@export var breathDuration : float = 1.0
@export var breathVelocityMagnitude : float = 1.0



var wishDir := Vector3.ZERO
var inputDir := Vector2.ZERO

var camAlignedWishDir := Vector3.ZERO
@export var noclipSpeedMult := 3.0
var noclip := false

@onready var leanPivot: Node3D = $LeanPivot
@onready var headPivot: Node3D = $LeanPivot/HeadPivot
@onready var head: Node3D = $LeanPivot/HeadPivot/Head
@onready var eyes: Node3D = $LeanPivot/HeadPivot/Head/Eyes
@onready var camera: Camera3D = $LeanPivot/HeadPivot/Head/Eyes/Camera3D
@onready var collision: CollisionShape3D = $CollisionShape3D
@onready var originalHeight = $CollisionShape3D.shape.height

func _ready() -> void:
	for child in $Visuals.find_children("*", "VisualInstance3D"):
		child.set_layer_mask_value(1, false)
		child.set_layer_mask_value(2, true)



func _headbob_effect(delta):
	var previousY: float = sin((headbobTime - delta) * headbobMoveFrequency) * headbobMoveAmount
	headbobTime += delta * self.velocity.length()

	var currentY: float = sin(headbobTime * headbobMoveFrequency) * headbobMoveAmount
	camera.transform.origin = Vector3(
		cos(headbobTime * headbobMoveFrequency * 0.5) * headbobMoveAmount,
		currentY,
		0
	)

	# Detect when we cross from moving down to moving up (lowest point)
	if previousY < 0 and currentY > 0:
		footstepPlayer.play()

func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
	elif  event.is_action_pressed("ui_cancel"):
		Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)

	if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		if event is InputEventMouseMotion:
			rotate_y(-event.relative.x * lookSensitivity)
			camera.rotate_x(-event.relative.y * lookSensitivity)
			camera.rotation.x = clamp(camera.rotation.x, deg_to_rad(-90), deg_to_rad(90))




func _run_body_test_motion(from: Transform3D, motion: Vector3, result = null) -> bool:
	if not result: result = PhysicsTestMotionResult3D.new()
	var params = PhysicsTestMotionParameters3D.new()
	params.from = from
	params.motion = motion
	return PhysicsServer3D.body_test_motion(self.get_rid(), params, result)

var _saved_camera_global_pos = null
func _save_camera_pos_for_smoothing():
	if _saved_camera_global_pos == null:
		_saved_camera_global_pos = eyes.global_position

func slide_camera_smooth_back_to_origin(delta):
	if _saved_camera_global_pos == null: return
	eyes.global_position.y = _saved_camera_global_pos.y
	eyes.position.y = clampf(eyes.position.y, -crouchTranslate, crouchTranslate) # Clamp incase teleported
	var move_amount = max(self.velocity.length() * delta, walkSpeed/2 * delta)
	eyes.position.y = move_toward(eyes.position.y, 0.0, move_amount)
	_saved_camera_global_pos = eyes.global_position
	if eyes.position.y == 0:
		_saved_camera_global_pos = null # Stop smoothing camera

func handle_crouch(delta) -> void:
	var was_crouched_last_frame = is_crouched
	if Input.is_action_pressed("Crouch"):
		is_crouched = true
	elif is_crouched and not self.test_move(self.global_transform, Vector3(0,crouchTranslate,0)):
		is_crouched = false

	# Allow for crouch to heighten/extend a jump
	var translate_y_if_possible := 0.0
	if was_crouched_last_frame != is_crouched and not is_on_floor() and not snappedToStairLastFrame:
		translate_y_if_possible = crouchJumpAdd if is_crouched else -crouchJumpAdd
	# Make sure not to get player stuck in floor/ceiling during crouch jumps
	if translate_y_if_possible != 0.0:
		var result = KinematicCollision3D.new()
		self.test_move(self.global_transform, Vector3(0,translate_y_if_possible,0), result)
		self.position.y += result.get_travel().y
		head.position.y -= result.get_travel().y
		head.position.y = clampf(head.position.y, -crouchTranslate, 0)

	head.position.y = move_toward(head.position.y, -crouchTranslate if is_crouched else 0.0, 7.0 * delta)
	$CollisionShape3D.shape.height = originalHeight - crouchTranslate if is_crouched else originalHeight
	$CollisionShape3D.position.y = $CollisionShape3D.shape.height / 2

func get_move_speed() -> float:
	if is_crouched or is_leaning:
		return walkSpeed * 0.6
	return sprintSpeed if Input.is_action_pressed("Sprint") else walkSpeed



func _handle_noclip(delta: float) -> bool:
	if(Input.is_action_just_pressed("_noclip") and OS.has_feature("debug")):
		noclip = !noclip
		print(noclip)

	collision.disabled = noclip

	if not noclip:
		return false

	var speed: float = get_move_speed() * noclipSpeedMult
	if Input.is_action_pressed("Sprint"):
		speed * 3.0

	self.velocity = camAlignedWishDir * speed
	global_position += self.velocity * delta

	return true

func _handle_ground_physics(delta: float):

	var curSpeedInWishDir: float = self.velocity.dot(wishDir)
	var addSpeedTilCap: float    = get_move_speed() - curSpeedInWishDir
	if addSpeedTilCap > 0:
		var accelSpeed: float = groundAccel * airMoveSpeed * delta
		accelSpeed = min(accelSpeed, addSpeedTilCap)
		self.velocity += accelSpeed * wishDir


	var control = max(self.velocity.length(), groundDeccel)
	var drop = control * groundFriction * delta
	var newSpeed = max(self.velocity.length() - drop, 0.0)
	if self.velocity.length() > 0:
		newSpeed /= self.velocity.length()
	self.velocity *= newSpeed

	_headbob_effect(delta)



func clip_velocity(normal: Vector3, overbounce: float, delta: float) -> void:
	var backoff := self.velocity.dot(normal) * overbounce
	if backoff >= 0: return

	var change := normal * backoff
	self.velocity -= change
	var adjust := self.velocity.dot(normal)
	if adjust < 0.0:
		self.velocity -= normal * adjust



func snap_down_to_stair_check() -> void:
	var did_snap := false
	var floor_below : bool = stairsBelowRaycast3D.is_colliding() and not is_surface_too_steep(stairsBelowRaycast3D.get_collision_normal())
	var wasOnFloorLastFrame = Engine.get_physics_frames() == lastFrameWasOnFloor
	if not is_on_floor() and velocity.y <= 0 and (wasOnFloorLastFrame or snappedToStairLastFrame) and floor_below:
		var body_test_result = PhysicsTestMotionResult3D.new()
		if _run_body_test_motion(self.global_transform, Vector3(0, -maxStepHeight, 0), body_test_result):
			_save_camera_pos_for_smoothing()
			var translate_y = body_test_result.get_travel().y
			self.position.y += translate_y
			apply_floor_snap()
			did_snap = true
	snappedToStairLastFrame = did_snap

func snap_up_stairs_check(delta: float) -> bool:
	if not is_on_floor() and not snappedToStairLastFrame: return false
	var expected_move_motion: Vector3        = self.velocity * Vector3(1,0,1) * delta
	var step_pos_with_clearance: Transform3D = self.global_transform.translated(expected_move_motion + Vector3(0, maxStepHeight, 0))
	var down_check_result                    = PhysicsTestMotionResult3D.new()
	if _run_body_test_motion(step_pos_with_clearance, Vector3(0, -maxStepHeight * 2, 0), down_check_result) and (down_check_result.get_collider().is_class("StaticBody3D") or down_check_result.get_collider().is_class("CSGShape3D")):
		var step_height =  ((step_pos_with_clearance.origin + down_check_result.get_travel()) - self.global_position).y
		if step_height > maxStepHeight or step_height <= 0.01 or (down_check_result.get_collision_point() - self.global_position).y > maxStepHeight: return false
		stairsAheadRaycast3D.global_position = down_check_result.get_collision_point() + Vector3(0, maxStepHeight, 0) + expected_move_motion.normalized() * 0.1
		stairsAheadRaycast3D.force_raycast_update()
		if stairsAheadRaycast3D.is_colliding() and not is_surface_too_steep(stairsAheadRaycast3D.get_collision_normal()):
			_save_camera_pos_for_smoothing()
			self.global_position = step_pos_with_clearance.origin + down_check_result.get_travel()
			apply_floor_snap()
			snappedToStairLastFrame = true
			return true
	return false

func is_surface_too_steep(normal: Vector3) -> bool:
	var maxSlopeAngleDot: float = Vector3(0,1,0).rotated(Vector3(1.0,0,0), self.floor_max_angle).dot(Vector3(0,1,0))
	if normal.dot(Vector3(0,1,0)) < maxSlopeAngleDot:
		return true
	return false

func _handle_air_physics(delta: float):
	self.velocity.y -= ProjectSettings.get_setting("physics/3d/default_gravity") * delta

	# Air movement physics thanks to the god John Carmack
	var curSpeedInWishDir: float = self.velocity.dot(wishDir)
	var cappedSpeed              = min((airMoveSpeed * wishDir).length(), airCap)
	var addSpeedTilCap    = cappedSpeed - curSpeedInWishDir
	if addSpeedTilCap > 0 :
		var accelSpeed: float = airAccel * airMoveSpeed * delta
		accelSpeed = min(accelSpeed, addSpeedTilCap)
		self.velocity += accelSpeed * wishDir

	if is_on_wall():
		if is_surface_too_steep(get_wall_normal()):
			self.motion_mode = CharacterBody3D.MOTION_MODE_FLOATING
		else:
			self.motion_mode = CharacterBody3D.MOTION_MODE_GROUNDED
		clip_velocity(get_wall_normal(), 1, delta)


func _physics_process(delta: float) -> void:
	if is_on_floor() or snappedToStairLastFrame: lastFrameWasOnFloor = Engine.get_physics_frames()
	inputDir = Input.get_vector("Left", "Right", "Forward", "Backward").normalized()
	wishDir = self.global_transform.basis * Vector3(inputDir.x, 0., inputDir.y)
	camAlignedWishDir = camera.global_transform.basis * Vector3(inputDir.x, 0., inputDir.y)


	handle_crouch(delta)
	handle_lean(delta)

	if not _handle_noclip(delta) and not handle_ladder_physics():
		if is_on_floor() or snappedToStairLastFrame:
			if Input.is_action_just_pressed("Jump") or (autoBhop and Input.is_action_pressed("Jump")):
				self.velocity.y = jumpVelocity
			_handle_ground_physics(delta)
		else:
			_handle_air_physics(delta)

		if not snap_up_stairs_check(delta):
			move_and_slide()
			snap_down_to_stair_check()

	slide_camera_smooth_back_to_origin(delta)

func _process(delta: float) -> void:
	handle_breath(delta)
	pass


var _cur_ladder_climbing : Area3D = null
func handle_ladder_physics() -> bool:
	# Keep track of whether already on ladder. If not already, check if overlapping a ladder area3d.
	var was_climbing_ladder := _cur_ladder_climbing and _cur_ladder_climbing.overlaps_body(self)
	if not was_climbing_ladder:
		_cur_ladder_climbing = null
		for ladder in get_tree().get_nodes_in_group("ladder_area3d"):
			if ladder.overlaps_body(self):
				_cur_ladder_climbing = ladder
				break
	if _cur_ladder_climbing == null:
		return false

	# Set up variables. Most of this is going to be dependent on the player's relative position/velocity/input to the ladder.
	var ladder_gtransform : Transform3D = _cur_ladder_climbing.global_transform
	var pos_rel_to_ladder := ladder_gtransform.affine_inverse() * self.global_position

	var forward_move := Input.get_action_strength("Forward") - Input.get_action_strength("Backward")
	var side_move                    := Input.get_action_strength("Right") - Input.get_action_strength("Left")
	var ladder_forward_move: Vector3 = ladder_gtransform.affine_inverse().basis * camera.global_transform.basis * Vector3(0, 0, -forward_move)
	var ladder_side_move: Vector3    = ladder_gtransform.affine_inverse().basis * camera.global_transform.basis * Vector3(side_move, 0, 0)

	# Strafe velocity is simple. Just take x component rel to ladder of both
	var ladder_strafe_vel : float = climb_speed * (ladder_side_move.x + ladder_forward_move.x)
	# For climb velocity, there are a few things to take into account:
	# If strafing directly into the ladder, go up, if strafing away, go down
	var ladder_climb_vel : float = climb_speed * -ladder_side_move.z
	# When pressing forward & facing the ladder, the player likely wants to move up. Vice versa with down.
	# So we will bias the direction (up/down) towards where we are looking by 45 degrees to give a greater margin for up/down detect.
	var up_wish := Vector3.UP.rotated(Vector3(1,0,0), deg_to_rad(-45)).dot(ladder_forward_move)
	ladder_climb_vel += climb_speed * up_wish

	# Only begin climbing ladders when moving towards them & prevent sticking to top of ladder when dismounting
	# Trying to best match the player's intention when climbing on ladder
	var should_dismount: bool = false
	if not was_climbing_ladder:
		var mounting_from_top = pos_rel_to_ladder.y > _cur_ladder_climbing.get_node("TopOfLadder").position.y
		if mounting_from_top:
			# They could be trying to get on from the top of the ladder, or trying to leave the ladder.
			if ladder_climb_vel > 0: should_dismount = true
		else:
			# If not mounting from top, they are either falling or on floor.
			# In which case, only stick to ladder if intentionally moving towards
			if (ladder_gtransform.affine_inverse().basis * wishDir).z >= 0: should_dismount = true
		# Only stick to ladder if very close. Helps make it easier to get off top & prevents camera jitter
		if abs(pos_rel_to_ladder.z) > 0.1: should_dismount = true

	# Let player step off onto floor
	if is_on_floor() and ladder_climb_vel <= 0: should_dismount = true

	if should_dismount:
		_cur_ladder_climbing = null
		return false

	# Allow jump off ladder mid climb
	if was_climbing_ladder and Input.is_action_just_pressed("Jump"):
		self.velocity = _cur_ladder_climbing.global_transform.basis.z * jumpVelocity * 1.5
		_cur_ladder_climbing = null
		return false

	self.velocity = ladder_gtransform.basis * Vector3(ladder_strafe_vel, ladder_climb_vel, 0)
	#self.velocity = self.velocity.limit_length(climb_speed) # Uncomment to turn off ladder boosting

	# Snap player onto ladder
	pos_rel_to_ladder.z = 0
	self.global_position = ladder_gtransform * pos_rel_to_ladder

	move_and_slide()
	return true


func handle_lean(delta: float):
	var leanValue: float = Input.get_axis("LeanLeft", "LeanRight")
	var targetLean: float = atan(leanAmount * leanValue)
	is_leaning = true if targetLean != 0 else false
	leanPivot.rotation.z = (lerp_angle(leanPivot.rotation.z, targetLean, delta * leanSpeed))


func handle_breath(delta: float):
	breathTime += delta
	var mag: float = ((self.velocity.length() * breathVelocityMagnitude) if self.velocity.length() != 0 and is_on_floor()  else 1) if not noclip else 0
	var forward_move := -(Input.get_action_strength("Forward") - Input.get_action_strength("Backward")) * mag
	var side_move	 := -(Input.get_action_strength("Right") - Input.get_action_strength("Left"))  * mag
	var t: float   = fmod(breathTime, breathDuration) / breathDuration  # Add a breathDuration variable
	var pointPos: Vector3 = Vector3(breathPosCurve.curve_x.sample_baked(t), breathPosCurve.curve_y.sample_baked(t), breathPosCurve.curve_z.sample_baked(t))
	var pointRot: Vector3 = Vector3(breathRotCurve.curve_x.sample_baked(t), breathRotCurve.curve_y.sample_baked(t), breathRotCurve.curve_z.sample_baked(t))

	eyes.position = eyes.position.lerp(Vector3(pointPos.x * forward_move, pointPos.y * mag, pointPos.z * side_move), mag * delta)
	eyes.rotation = eyes.rotation.lerp(Vector3(pointRot.x * forward_move, pointRot.y * mag, pointRot.z * side_move), mag * delta)
