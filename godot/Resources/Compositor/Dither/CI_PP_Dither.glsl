#[compute]
#version 450
layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(rgba16f, set = 0, binding = 0) uniform image2D color_image;

layout(push_constant, std430) uniform Params {
vec2 raster_size;     // 2 floats (8 bytes)
float dithering_scale; // 1 int (4 bytes)
float ditherAmount;      // 1 float (4 bytes)
float reserved2;      // 1 float (4 bytes)
float reserved3;      // 1 float (4 bytes)
} params;

int dithering_pattern(ivec2 fragcoord) {
const int pattern[16] = int[](
-4, 0, -3, 1,
2, -2, 3, -1,
-3, 1, -4, 0,
3, -1, 2, -2
);

int x = fragcoord.x % 4;
int y = fragcoord.y % 4;

return pattern[y * 4 + x];
}

void main() {
ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
ivec2 size = ivec2(params.raster_size);

if (uv.x >= size.x || uv.y >= size.y) {
return;
}

vec4 color = imageLoad(color_image, uv);

ivec3 c = ivec3(round(color.rgb * 255.0));

ivec2 scaled_uv = ivec2(floor(vec2(uv) / params.dithering_scale));
c += (ivec3(dithering_pattern(scaled_uv) * params.ditherAmount));
c = clamp(c, 0, 255); // Ensure the values are clamped to the 0-255 range


color.rgb = vec3(c) / 255.0; // Convert back to the 0.0-1.0 range

imageStore(color_image, uv, color);
}
