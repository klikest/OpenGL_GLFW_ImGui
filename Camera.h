#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>


class Camera
{
public:
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float cam_speed = 20;

    GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
    GLfloat pitch = 0.0f;
    GLfloat lastX;
    GLfloat lastY;
    int width, height;
    GLfloat fov = 45.0f;
    bool firstMouse = true;

    glm::mat4 pMat;
    glm::mat4 vMat;

    GLuint vLoc = 0, projLoc = 0;

    Camera(GLFWwindow* window, glm::vec3 campos_, float yaw_, float pitch);
    void MoveCamera(GLFWwindow* window, GLfloat deltaTime);
    void UpdateMatrix(GLuint shader, GLuint shader_coords, GLuint shader_rect);

};

