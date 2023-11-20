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
#include "Camera.h"



    Camera::Camera(GLFWwindow* window, glm::vec3 campos_, float yaw_, float pitch_)
    {
        cameraPos = campos_;
        glfwGetFramebufferSize(window, &width, &height);
        float aspect = (float)width / (float)height;

        yaw = yaw_;
        pitch = pitch_;
        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);


        pMat = glm::perspective(1.0472f, aspect, 0.1f, 10000.0f); // 1.0472 radians == 60 degrees
        vMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        lastX = (GLfloat)(width / 2.0);
        lastY = (GLfloat)(height / 2.0);
    }


    void Camera::MoveCamera(GLFWwindow* window, GLfloat deltaTime)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        // Camera controls
        GLfloat cameraSpeed = cam_speed * deltaTime;;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraUp;
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraUp;
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        {
      

        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            if (firstMouse)
            {
                lastX = (GLfloat)xpos;
                lastY = (GLfloat)ypos;
                firstMouse = false;
            }

            GLfloat xoffset = (GLfloat)(xpos - lastX);
            GLfloat yoffset = (GLfloat)(lastY - ypos); // Reversed since y-coordinates go from bottom to left
            lastX = (GLfloat)xpos;
            lastY = (GLfloat)ypos;

            GLfloat sensitivity = 0.05f;	// Change this value to your liking
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            yaw += xoffset;
            pitch += yoffset;

            // Make sure that when pitch is out of bounds, screen doesn't get flipped
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;

            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            cameraFront = glm::normalize(front);

        }

        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
        {
            // Unhides cursor since camera is not looking around anymore
            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            // Makes sure the next time the camera looks around it doesn't jump
            firstMouse = true;
        }

        vMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


    }

    void Camera::UpdateMatrix(GLuint shader, GLuint shader_coords, GLuint shader_rect)
    {
        glUseProgram(shader);

        vLoc = glGetUniformLocation(shader, "v_matrix");
        projLoc = glGetUniformLocation(shader, "proj_matrix");

        glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        glUseProgram(shader_coords);

        vLoc = glGetUniformLocation(shader_coords, "mv_matrix");
        projLoc = glGetUniformLocation(shader_coords, "proj_matrix");

        glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        glUseProgram(shader_rect);

        vLoc = glGetUniformLocation(shader_rect, "mv_matrix");
        projLoc = glGetUniformLocation(shader_rect, "proj_matrix");

        glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    }

