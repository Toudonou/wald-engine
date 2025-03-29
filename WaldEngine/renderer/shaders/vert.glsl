#version  430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;
layout (location = 3) in float texIndex;
layout (location = 4) in vec4 center;
layout (location = 5) in float radiusValue;


uniform mat4 pr_matrix = mat4(1.0); // Convert the world space to the screen space
uniform mat4 vw_matrix = mat4(1.0); // Represent the camera
uniform mat4 ml_matrix = mat4(1.0); // Represent the object transformation : not needed for now

out vec4 pos;
out vec2 texCoord;
out vec4 colour;
out float tex_index;
out vec4 centerPos;
out float radius;

void main() {
    gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
    pos = gl_Position;
    centerPos =  center;
    radius = radiusValue;
    colour = color;
    tex_index = texIndex;
    texCoord = uv;
}