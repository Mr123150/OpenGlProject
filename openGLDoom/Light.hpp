//
//  Light.hpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 01.05.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include <iostream>

class Light{
public:
    Light() =default;
    Light(const GLuint& _prog, const glm::vec3& _pos, const glm::vec3& _color);
    Light(const Light& l);
    Light& operator =(const Light& l);
    
    void render();
    void setup(const GLfloat& _ambient, const GLfloat& _attenuation) {ambient = _ambient; attenuation = _attenuation;}
protected:
    GLuint program;
    glm::vec3 pos;
    glm::vec3 color;
    
    GLfloat ambient;
    GLfloat attenuation;
};

#endif /* Light_hpp */
