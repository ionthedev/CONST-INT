#[compute]
#version 450
layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(rgba16f, set = 0, binding = 0) uniform image2D color_image;

layout(push_constant, std430) uniform Params {
vec2 raster_size;
float colors;
vec2 reserved;
} params;

float reduce_color(float raw, float depth) {
if (depth >= 256.0) {
return raw; // Full color range, no change
}
float div = 1.0 / depth;
float val = 0.0;
for (int i = 0; i < int(depth); ++i) {
if (raw > div * (float(i) + 1.0)) {
continue;
}
val = div * float(i) + div;
break;
}
return val;
}

void main() {
ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
ivec2 size = ivec2(params.raster_size);

if (uv.x >= size.x || uv.y >= size.y) {
return;
}

vec4 color = imageLoad(color_image, uv);

float depth = params.colors;
color.r = reduce_color(color.r, depth);
color.g = reduce_color(color.g, depth);
color.b = reduce_color(color.b, depth);

imageStore(color_image, uv, color);
}
