//
//  Camera.cpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 24.04.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#include "Camera.hpp"

#include <cmath>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(const GLuint& _prog, const glm::mat4& _proj){
    program = _prog;
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    rot = 0.0f;
    projection = _proj;
}

Camera::Camera(const Camera& c){
    program = c.program;
    pos = c.pos;
    rot = c.rot;
    projection = c.projection;
}

Camera& Camera::operator=(const Camera& c){
    program = c.program;
    pos = c.pos;
    rot = c.rot;
    projection = c.projection;
    
    return *this;
}

void Camera::move(const glm::vec3& _pos){
    pos[0]+=(_pos[0]*cos(glm::radians(rot))-_pos[2]*sin(glm::radians(rot)));
    pos[2]+=(_pos[0]*sin(glm::radians(rot))+_pos[2]*cos(glm::radians(rot)));
}

void Camera::render(){
    glUseProgram(program);
    
    while(rot>360) rot-=360;
    while(rot<0) rot+=360;
    
    glm::vec3 view = pos + glm::vec3(cos(glm::radians(rot)),0,sin(glm::radians(rot)));
    glm::mat4 camera = glm::lookAt(pos, view, glm::vec3(0,1,0));
    
    //GLuint uniformProjection = glGetUniformLocation(program, "projection");
    //glUniformMatrix4fv(uniformProjection,1,GL_FALSE,glm::value_ptr(projection));
    
    GLuint uniformCamera = glGetUniformLocation(program, "camera");
    glUniformMatrix4fv(uniformCamera,1,GL_FALSE,glm::value_ptr(projection*camera));
    
    glUniform3fv(glGetUniformLocation(program, "cameraPos"),1,glm::value_ptr(pos));
    
    glUseProgram(0);

}
