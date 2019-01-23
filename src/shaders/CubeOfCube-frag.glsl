#version 300 es

// This is a fragment shader. If you've opened this file first, please
// open and read lambert.vert.glsl before reading on.
// Unlike the vertex shader, the fragment shader actually does compute
// the shading of geometry. For every pixel in your program's output
// screen, the fragment shader is run for every bit of geometry that
// particular pixel overlaps. By implicitly interpolating the position
// data passed into the fragment shader by the vertex shader, the fragment shader
// can compute what color to apply to its pixel based on things like vertex
// position, light position, and vertex color.
precision highp float;

uniform vec4 u_Color; // The color with which to render this instance of geometry.

// These are the interpolated values out of the rasterizer, so you can't know
// their specific values without knowing the vertices that contributed to them
in vec4 fs_Nor;
in vec4 fs_LightVec;
in vec4 fs_Col;

out vec4 out_Col; // This is the final output color that you will see on your
                  // screen for the pixel that is currently being processed.


void main()
{
    vec3 leftColor =  vec3(  3, 130,  75) / 255.0;
    vec3 frontColor = vec3(233, 207,  12) / 255.0;
    vec3 topColor =   vec3(215,  75,   4) / 255.0;
    
    vec3 color;
    color = mix(color, leftColor,  abs( dot(fs_Nor.rgb, vec3(1,0,0) ) ) );
    color = mix(color, frontColor, abs( dot(fs_Nor.rgb, vec3(0,0,1) ) ) );
    color = mix(color, topColor,   abs( dot(fs_Nor.rgb, vec3(0,1,0) ) ) );

    out_Col = vec4(color.rgb, 1);

}