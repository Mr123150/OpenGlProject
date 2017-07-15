//
//  Box.hpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 12.04.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Box{
public:
    Box(const GLuint _program, const glm::vec3 _coord, const bool _solid, const std::string& _texPath);
    Box(const Box& b);
    Box& operator =(const Box& b);
    
    ~Box();
    
    void render();
    void setShine(GLfloat _shine, glm::vec3 _color) {shine = _shine; color = _color;}
    
    bool isSolid() const {return solid;}
    
protected:
    GLuint program;
    GLuint vao;
    GLuint vbo;
    std::vector<GLfloat> vertexData;
    
    bool solid;
    glm::vec3 pos;
    GLuint tex;
    
    GLfloat shine = 0;
    glm::vec3 color = glm::vec3(1, 1, 1);
};

#endif /* Box_hpp */
