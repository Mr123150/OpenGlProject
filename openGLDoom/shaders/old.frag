#version 150

uniform sampler2D tex;

in vec2 fTex;
out vec4 color;

void main(void) {
    color = texture(tex, fTex);
}
