//
//  Scene.cpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 17.04.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#include "Scene.hpp"

#include <vector>
#include <cstring>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.hpp"

Scene::Scene(GLFWwindow* _window, const Camera& _cam){
    window = _window;
    camera = _cam;
}

Scene::Scene(const Scene& s){
    camera = s.camera;
    
    boxes = s.boxes;
}

Scene& Scene::operator=(const Scene& s){
    camera = s.camera;
    
    boxes = s.boxes;
    
    return *this;
}

void Scene::render(){
    glClearColor(0.25f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    camera.render();
    light.render();
    
    for(Box b:boxes){
        b.render();
    }
}

void Scene::update(){
    
}

void Scene::input(int key, int action){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        camera.move(glm::vec3(0.1,0,0));
    }
    else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        camera.move(glm::vec3(-0.1,0,0));
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        camera.rotate(-1);
    }
    else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        camera.rotate(1);
    }
    
    if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        camera.move(glm::vec3(0,0,-0.1));
    }
    else if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        camera.move(glm::vec3(0,0,0.1));
    }
}
