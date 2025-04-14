@tool
extends CompositorEffect
class_name RetroEffect

var rd: RenderingDevice
var shader: RID
var pipeline: RID

# Pixelation
@export_group("Pixelation")
@export var pixel_size: int = 1:
	get:
		return pixel_size
	set(value):
		pixel_size = max(1, value)  # Minimum of 1 (disabled)

# Color Depth
@export_group("Color Depth")
@export var enable_dithering: bool = false:
	get:
		return enable_dithering
	set(value):
		enable_dithering = value
		notify_property_list_changed()

# Dithering parameters (only shown when dithering is enabled)
var dither_scale: float = 1.0:
	get:
		return dither_scale
	set(value):
		dither_scale = clamp(value, 0.5, 10.0)

@export_range(0.0, 2.0, 0.1) var dither_amount: float = 1.0:
	get:
		return dither_amount
	set(value):
		dither_amount = clamp(value, 0.0, 2.0)

func _init() -> void:
	effect_callback_type = EFFECT_CALLBACK_TYPE_POST_TRANSPARENT
	rd = RenderingServer.get_rendering_device()
	RenderingServer.call_on_render_thread(_initialize_compute)

func _notification(what: int) -> void:
	if what == NOTIFICATION_PREDELETE:
		if shader.is_valid():
			RenderingServer.free_rid(shader)

func _initialize_compute() -> void:
	rd = RenderingServer.get_rendering_device()
	if not rd:
		return

	var shader_file := load("res://Resources/Compositor/PSX/psx.glsl")
	var shader_spirv: RDShaderSPIRV = shader_file.get_spirv()

	shader = rd.shader_create_from_spirv(shader_spirv)
	if shader.is_valid():
		pipeline = rd.compute_pipeline_create(shader)

func _render_callback(p_effect_callback_type: EffectCallbackType, p_render_data: RenderData) -> void:
	if rd and p_effect_callback_type == EFFECT_CALLBACK_TYPE_POST_TRANSPARENT and pipeline.is_valid():
		var render_scene_buffers := p_render_data.get_render_scene_buffers()
		if render_scene_buffers:
			var size: Vector2i = render_scene_buffers.get_internal_size()
			if size.x == 0 and size.y == 0:
				return

			var x_groups := (size.x - 1) / 8 + 1
			var y_groups := (size.y - 1) / 8 + 1
			var z_groups := 1

			# Pack all parameters into the push constant array
			var push_constant := PackedFloat32Array([
			size.x,                          # raster_size.x
			size.y,                          # raster_size.y
			float(pixel_size),               # pixel_size
			256.0,                          # colors (fixed to 256 for 24-bit when dithering off)
			1.0 if enable_dithering else 0.0, # dither_enabled
			dither_amount,                   # dither_amount
			dither_scale,                    # dither_scale
			0.0                              # padding to maintain alignment
			])

			var view_count: int = render_scene_buffers.get_view_count()
			for view in view_count:
				var input_image: RID = render_scene_buffers.get_color_layer(view)

				var uniform := RDUniform.new()
				uniform.uniform_type = RenderingDevice.UNIFORM_TYPE_IMAGE
				uniform.binding = 0
				uniform.add_id(input_image)
				var uniform_set := UniformSetCacheRD.get_cache(shader, 0, [uniform])

				var compute_list := rd.compute_list_begin()
				rd.compute_list_bind_compute_pipeline(compute_list, pipeline)
				rd.compute_list_bind_uniform_set(compute_list, uniform_set, 0)
				rd.compute_list_set_push_constant(compute_list, push_constant.to_byte_array(), push_constant.size() * 4)
				rd.compute_list_dispatch(compute_list, x_groups, y_groups, z_groups)
				rd.compute_list_end()

func _get_property_list() -> Array:
	var properties: Array = []

	# Only show dithering parameters when dithering is enabled
	if enable_dithering:
		properties.append({
			"name": "dither_scale",
			"type": TYPE_FLOAT,
			"usage": PROPERTY_USAGE_DEFAULT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "0.5,10.0,0.5"
		})
		properties.append({
			"name": "dither_amount",
			"type": TYPE_FLOAT,
			"usage": PROPERTY_USAGE_DEFAULT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "0.0,2.0,0.1"
		})

	return properties