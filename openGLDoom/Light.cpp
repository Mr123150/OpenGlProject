//
//  Light.cpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 01.05.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#include "Light.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

Light::Light(const GLuint& _prog, const glm::vec3& _pos, const glm::vec3& _color){
    program = _prog;
    pos = _pos;
    color = _color;
}

Light::Light(const Light& l){
    program = l.program;
    pos = l.pos;
    color = l.color;
}

Light& Light::operator=(const Light &l){
    program = l.program;
    pos = l.pos;
    color = l.color;
    
    return *this;
}

void Light::render(){
    glUseProgram(program);
    
    glUniform3fv(glGetUniformLocation(program, "light.position"),1,glm::value_ptr(pos));
    glUniform3fv(glGetUniformLocation(program, "light.color"),1,glm::value_ptr(color));
    glUniform1f(glGetUniformLocation(program, "light.ambient"),ambient);
    glUniform1f(glGetUniformLocation(program, "light.attenuation"),attenuation);
    
    glUseProgram(0);
}
