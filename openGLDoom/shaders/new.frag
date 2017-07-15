#version 150

uniform mat4 model;
uniform sampler2D tex;

uniform struct Light {
    vec3 position;
    vec3 color;
} light;

in vec3 fCoord;
in vec2 fTex;
in vec3 fNorm;

out vec4 color;

void main(void) {
    mat3 nMatrix = transpose(invert(mat3(model)));
    vec3 normal = normalize(nMatrix * fNorm);
    
    vec3 fPos = vec3(model * vec4(fCoord, 1));
    
    vec3 lightVector = light.position - fPos;
    
    float brightness = dot(normal, lightVector) / (length(lightVector) * length(normal));
    brightness = clamp(brightness, 0, 1);
    
    vec4 surfaceColor = texture(tex, fTex);
    color = vec4(brightness * light.color * surfaceColor.rgb, surfaceColor.a);
}
