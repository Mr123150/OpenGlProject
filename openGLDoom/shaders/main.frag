#version 150

uniform sampler2D tex;
uniform mat4 model;

uniform vec3 cameraPos;

uniform struct Light {
    vec3 position;
    vec3 color;
    float ambient;
    float attenuation;
} light;

uniform struct Material {
    float shine;
    vec3 color;
} material;

in vec3 fCoord;
in vec2 fTex;
in vec3 fNorm;

out vec4 color;

void main(void) {
    mat3 nMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(nMatrix * fNorm);
    
    vec3 surfPos = vec3(model * vec4(fCoord, 1));
    vec3 surfLight = normalize(light.position - surfPos);
    vec4 surfColor = texture(tex, fTex);
    
    float diffuseCoef = max(0.0, dot(normal, surfLight));
    vec3 diffuse = diffuseCoef * surfColor.rgb * light.color;
    
    vec3 ambient = light.ambient * surfColor.rgb * light.color;
    
    vec3 incidence = -surfLight;
    vec3 reflection = reflect(incidence, normal);
    vec3 surfCamera = normalize(cameraPos - surfPos);
    float cosAngle = max(0.0, dot(surfCamera, reflection));
    float specularCoef = pow(cosAngle, material.shine);
    vec3 specular = specularCoef * material.color * light.color;
    
    float distLight = length(light.position - surfPos);
    float attenuation = 1.0/(1.0 + light.attenuation * pow(distLight, 2));
    
    vec3 linearColor = ambient + attenuation * (diffuse + specular);
    
    vec3 gamma = vec3(1.0/2.2);
    color = vec4(pow(linearColor, gamma), surfColor.a);
}
