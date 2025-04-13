#[compute]
#version 450
layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(rgba16f, set = 0, binding = 0) uniform image2D color_image;

layout(push_constant, std430) uniform Params {
    vec2 raster_size;
    float colors;
    vec2 reserved;
} params;

// Convert from linear to sRGB space
vec3 linear_to_srgb(vec3 linear) {
    vec3 cutoff = vec3(lessThan(linear, vec3(0.0031308)));
    vec3 higher = vec3(1.055) * pow(linear, vec3(1.0/2.4)) - vec3(0.055);
    vec3 lower = linear * vec3(12.92);
    return mix(higher, lower, cutoff);
}

// Convert from sRGB to linear space
vec3 srgb_to_linear(vec3 srgb) {
    vec3 cutoff = vec3(lessThan(srgb, vec3(0.04045)));
    vec3 higher = pow((srgb + vec3(0.055)) / vec3(1.055), vec3(2.4));
    vec3 lower = srgb / vec3(12.92);
    return mix(higher, lower, cutoff);
}

float reduce_color(float raw, float depth) {
    if (depth >= 256.0) {
        return raw; // Full color range, no change
    }
    float div = 1.0 / (depth - 1.0); // Adjust to include both 0 and 1
    float val = floor(raw * (depth - 1.0)) * div;
    return val;
}

void main() {
    ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = ivec2(params.raster_size);

    if (uv.x >= size.x || uv.y >= size.y) {
        return;
    }

    vec4 color = imageLoad(color_image, uv);
    
    // Convert from linear to sRGB for color reduction
    vec3 srgb_color = linear_to_srgb(color.rgb);
    
    float depth = params.colors;
    srgb_color.r = reduce_color(srgb_color.r, depth);
    srgb_color.g = reduce_color(srgb_color.g, depth);
    srgb_color.b = reduce_color(srgb_color.b, depth);
    
    // Convert back to linear space for storage
    color.rgb = srgb_to_linear(srgb_color);
    
    imageStore(color_image, uv, color);
}
