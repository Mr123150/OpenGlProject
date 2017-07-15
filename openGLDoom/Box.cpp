//
//  Box.cpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 12.04.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#include "Box.hpp"

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <il/il.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/ext.hpp"

Box::Box(const GLuint _program, const glm::vec3 _pos, const bool _solid, const std::string& _texPath){
    program = _program;
    pos = _pos;
    solid = _solid;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    vertexData = {
        //X   Y    Z        U     V       Normal
        // bottom
        -1.0f,-1.0f,-1.0f,  0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,  0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,  0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
        
        // top
        -1.0f, 1.0f,-1.0f,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,  0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,  0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        
        // front
        -1.0f,-1.0f, 1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
        
        // back
        -1.0f,-1.0f,-1.0f,  0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        -1.0f, 1.0f,-1.0f,  0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        -1.0f, 1.0f,-1.0f,  0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
        
        // left
        -1.0f,-1.0f, 1.0f,  0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,  1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
        -1.0f,-1.0f,-1.0f,  0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,  0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,  1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,  1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
        
        // right
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   1.0f, 0.0f, 0.0f
    };
    
    GLint attribCoord = glGetAttribLocation(program, "coord");
    
    glEnableVertexAttribArray(attribCoord);
    glVertexAttribPointer(attribCoord, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), NULL);
    
    GLint attribTex = glGetAttribLocation(program,"vTex");
    
    glEnableVertexAttribArray(attribTex);
    glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_TRUE, 8*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    
    GLint attribNorm = glGetAttribLocation(program,"vNorm");
    
    glEnableVertexAttribArray(attribNorm);
    glVertexAttribPointer(attribNorm, 3, GL_FLOAT, GL_TRUE, 8*sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));
    
    GLuint uniformTex = glGetUniformLocation(program, "tex");
    glUniform1i(uniformTex,0);
    
    ILuint imgTex;
    ILboolean success;
    
    ilGenImages(1, &imgTex);
    ilBindImage(imgTex);
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    
    success=ilLoadImage(_texPath.c_str());
    if (!success){
        ilDeleteImages(1, &imgTex);
        printf("Error while loading image");
        
        tex = 0;
    }
    else{
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    
        glGenTextures(1, &tex);
    
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);
    
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
        ilBindImage(0);
        ilDeleteImage(imgTex);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Box::Box(const Box& b){
    program = b.program;
    
    vertexData = b.vertexData;
    
    vao = b.vao;
    vbo = b.vbo;
    
    pos = b.pos;
    solid = b.solid;
    tex = b.tex;
}

Box& Box::operator=(const Box& b){
    program = b.program;
    
    vertexData = b.vertexData;
    
    vao = b.vao;
    vbo = b.vbo;
    
    pos = b.pos;
    solid = b.solid;
    tex = b.tex;
    
    return *this;
}

Box::~Box(){
    //glDeleteBuffers(1, &vbo);
    //glDeleteVertexArrays(1, &vao);
}

void Box::render(){
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    if(tex) glBindTexture(GL_TEXTURE_2D, tex);
    
    glUseProgram(program);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    
    glBufferData(GL_ARRAY_BUFFER, vertexData.size()*sizeof(GLfloat), &vertexData.front(), GL_STATIC_DRAW);
    
    glUniformMatrix4fv(glGetUniformLocation(program, "model"),1,GL_FALSE,glm::value_ptr(glm::translate(pos)));
    
    glUniform1f(glGetUniformLocation(program, "material.color"),shine);
    glUniform3fv(glGetUniformLocation(program, "material.color"),1,glm::value_ptr(color));
    
    glDrawArrays(GL_TRIANGLES, 0, 6*2*3);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glUseProgram(0);
}
