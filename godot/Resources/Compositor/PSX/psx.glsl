#[compute]
#version 450
layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(rgba16f, set = 0, binding = 0) uniform image2D color_image;

layout(push_constant, std430) uniform Params {
    vec2 raster_size;
    float pixel_size;      // For pixelation
    float colors;          // Color depth (256 for 8-bit per channel)
    float dither_enabled;  // 0.0 = disabled, 1.0 = enabled
    float dither_amount;   // Dithering intensity
    float dither_scale;    // Dithering pattern scale
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
        return raw;
    }
    float div = 1.0 / (depth - 1.0);
    float val = floor(raw * (depth - 1.0)) * div;
    return val;
}

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

    // Apply pixelation if enabled (pixel_size > 1.0)
    vec4 color;
    if (params.pixel_size > 1.0) {
        float x = float(int(gl_GlobalInvocationID.x) % int(params.pixel_size));
        float y = float(int(gl_GlobalInvocationID.y) % int(params.pixel_size));
        
        x = gl_GlobalInvocationID.x + floor(params.pixel_size / 2.0) - x;
        y = gl_GlobalInvocationID.y + floor(params.pixel_size / 2.0) - y;
        
        color = imageLoad(color_image, ivec2(x, y));
    } else {
        color = imageLoad(color_image, uv);
    }

    // Convert to sRGB for color processing
    vec3 srgb_color = linear_to_srgb(color.rgb);
    
    // Determine color depth based on dithering
    float depth = params.dither_enabled > 0.5 ? 32.0 : 256.0; // 15-bit (32 levels per channel) or 24-bit
    
    // Apply dithering if enabled
    if (params.dither_enabled > 0.5) {
        ivec2 scaled_uv = ivec2(floor(vec2(uv) / params.dither_scale));
        vec3 dither_offset = vec3(dithering_pattern(scaled_uv) * params.dither_amount) / 255.0;
        srgb_color += dither_offset;
    }
    
    // Apply color depth reduction
    srgb_color.r = reduce_color(srgb_color.r, depth);
    srgb_color.g = reduce_color(srgb_color.g, depth);
    srgb_color.b = reduce_color(srgb_color.b, depth);
    
    // Clamp colors
    srgb_color = clamp(srgb_color, 0.0, 1.0);
    
    // Convert back to linear space
    color.rgb = srgb_to_linear(srgb_color);
    
    imageStore(color_image, uv, color);
}