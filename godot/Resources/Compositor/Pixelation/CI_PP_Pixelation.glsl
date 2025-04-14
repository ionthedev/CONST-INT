#[compute]
#version 450
layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(rgba16f, set = 0, binding = 0) uniform image2D color_image;

layout(push_constant, std430) uniform Params {
    vec2 raster_size;
    float pixel_size;
    float reserved;
} params;

void main() {
    ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = ivec2(params.raster_size);

    if (uv.x >= size.x || uv.y >= size.y) {
        return;
    }

    float x = float(int(gl_GlobalInvocationID.x) % int(params.pixel_size));
    float y = float(int(gl_GlobalInvocationID.y) % int(params.pixel_size));

    x = gl_GlobalInvocationID.x + floor(params.pixel_size / 2.0) - x;
    y = gl_GlobalInvocationID.y + floor(params.pixel_size / 2.0) - y;

    vec4 color = imageLoad(color_image, ivec2(x, y));
    imageStore(color_image, uv, color);
}
