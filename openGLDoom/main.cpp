#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <il/il.h>

#include "Shader.hpp"
#include "Box.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

#include "GLShader.hpp"

GLFWwindow* window;

Scene scene;
Camera cam;

GLuint program;

const glm::vec2 SCREEN_SIZE(640, 480);

glm::mat4 projection;

GLfloat fps = 60;

void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void input(GLFWwindow* window, int key, int scancode, int action, int mods){
    scene.input(key, action);
}

void init(){
    if(!glfwInit()){
        fprintf(stderr, "Failed initialize GLFW.");
        exit(EXIT_FAILURE);
    }
    
    glfwSetErrorCallback(error_callback);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    window = glfwCreateWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "Test project", NULL, NULL);
    
    if(!window) {
        fprintf(stderr, "Failed to create GLFW window.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, input);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    ilInit();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

}

int main(){
    init();
    
    //program = glCreateProgram();
    
    //Shader vs = Shader("shaders/main.vert", GL_VERTEX_SHADER);
    //Shader fs = Shader("shaders/main.frag", GL_FRAGMENT_SHADER);
    
    program = LoadShader("shaders/main.vert", "shaders/main.frag");
    
    //glAttachShader(program, vs.object());
    //glAttachShader(program, fs.object());
    
    projection = glm::perspective(glm::radians(60.0f), SCREEN_SIZE.x/SCREEN_SIZE.y, 0.1f, 50.0f);
    
    glLinkProgram(program);
    
    cam = Camera(program, projection);
    cam.set(glm::vec3(3,0,3));
    cam.rotate(225);
    
    Box box1 = Box(program, glm::vec3(1,0,1), true, "img_test.png");
    Box box2 = Box(program, glm::vec3(1,0,-1), true, "img_test.png");
    
    box2.setShine(0.5,glm::vec3(1,0,0));
    
    Light light = Light(program, glm::vec3(3,0,1), glm::vec3(1,1,1));
    light.setup(1, 1);
    
    scene = Scene(window, cam);
    
    scene.setLight(light);
    
    scene.addBox(box1);
    scene.addBox(box2);
    
    double lastTime = glfwGetTime();
    double delta = 0;
    
    while(!glfwWindowShouldClose(window))
    {
        double currTime = glfwGetTime();
        delta += (currTime - lastTime)*fps;
        while(delta>1){
            --delta;
            scene.update();
        }
        lastTime = currTime;
        
        scene.render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}
