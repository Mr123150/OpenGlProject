//
//  Shader.cpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 12.04.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <assert.h>

Shader::Shader(){
    obj = 0;
    ref = NULL;
}

Shader::Shader(const std::string& path, GLenum type){
    obj = 0;
    ref = NULL;
    
    std::ifstream f;
    f.open(path.c_str(), std::ios::in | std::ios::binary);
    if(!f.is_open()) throw std::runtime_error(std::string("Failed to open file: ") + path);
    
    std::stringstream buffer;
    buffer << f.rdbuf() << '\n';
    
    const char* code = buffer.str().c_str();
    
    obj=glCreateShader(type);
    if(obj == 0) throw std::runtime_error("glCreateShader failed");
    
    glShaderSource(obj, 1, (const GLchar**)&code, NULL);
    glCompileShader(obj);
    
    GLint status;
    glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Compile failure in shader:\n");
        
        GLint infoLogLength;
        glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(obj, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        
        glDeleteShader(obj);
        obj = 0;
        throw std::runtime_error(msg);
    }
    
    ref = new unsigned;
    *ref = 1;
}

Shader::Shader(const Shader& s){
    obj = s.obj;
    ref = s.ref;
    
    attach();
}

Shader::~Shader(){
    if(ref) release();
}

Shader& Shader::operator =(const Shader& s){
    release();
    obj = s.obj;
    ref = s.ref;
    attach();
    
    return *this;
}

void Shader::attach(){
    assert(ref);
    *ref += 1;
}

void Shader::release(){
    assert(ref && *ref);
    *ref -= 1;
    if(!(*ref)){
        glDeleteShader(obj);
        obj=0;
        delete ref;
        ref = NULL;
    }
}
