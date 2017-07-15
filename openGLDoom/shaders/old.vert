#version 150

uniform mat4 camera;
uniform mat4 model;

in vec3 coord;
in vec2 vTex;

out vec2 fTex;

void main(void) {
    gl_Position = camera * model * vec4(coord, 1);
    
    fTex = vTex;
}
