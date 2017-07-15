//
//  Camera.hpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 24.04.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
public:
    Camera() =default;
    Camera(const GLuint& _prog, const glm::mat4& _proj);
    Camera(const Camera& c);
    Camera& operator =(const Camera& c);
    
    void set(const glm::vec3& _pos) {pos = _pos;}
    void move(const glm::vec3& _pos);
    void translate(const glm::vec3& _pos) {pos += _pos;}
    void rotate(const GLfloat& _rot) {rot += _rot;}
    
    void render();
protected:
    GLuint program;
    glm::vec3 pos;
    GLfloat rot;
    
    glm::mat4 projection;
};

#endif /* Camera_hpp */
