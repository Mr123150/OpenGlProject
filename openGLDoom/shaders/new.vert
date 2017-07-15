#version 150

uniform mat4 camera;
uniform mat4 model;

in vec3 coord;
in vec2 vTex;
in vec3 vNorm;

out vec3 fCoord;
out vec2 fTex;
out vec3 fNorm;

void main(void) {
    fCoord = coord;
    fTex = vTex;
    fNorm = vNorm;
    
    gl_Position = camera * model * vec4(coord, 1);
}
