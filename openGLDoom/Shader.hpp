//
//  Shader.hpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 12.04.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <GL/glew.h>

class Shader{
public:
    Shader();
    Shader(const std::string& path, GLenum type);
    GLuint object() const {return obj;}
    
    Shader(const Shader& s);
    Shader& operator =(const Shader& s);
    ~Shader();
protected:
    GLuint obj;
    unsigned* ref;
    
    void attach();
    void release();
};

#endif /* Shader_hpp */
