//
//  Scene.hpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 17.04.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Box.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class Scene{
public:
    Scene() =default;
    Scene(GLFWwindow* _window, const Camera& _cam);
    Scene(const Scene& s);
    Scene& operator=(const Scene& s);
    
    void addBox(Box& b) {boxes.push_back(b);}
    
    void setCamera(const glm::vec3& _pos) {camera.set(_pos);}
    void moveCamera(const glm::vec3& _pos) {camera.move(_pos);}
    void translateCamera(const glm::vec3& _pos) {camera.translate(_pos);}
    void rotateCamera(const GLfloat& _rot) {camera.rotate(_rot);}
    
    void setLight(const Light& l) {light = l;}
    
    void render();
    void update();
    void input(int key, int action);
    
protected:
    Camera camera;
    GLFWwindow* window;
    
    Light light;
    
    std::vector<Box> boxes;
};

#endif /* Scene_hpp */
