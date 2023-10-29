#pragma once
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include <GLFW/glfw3.h>
#include "Grid.h"

class UI_Data
{
public:
    glm::vec3 camPos;
    float cam_yaw;
    float cam_pitch;
    float cam_speed;
    float delta_time;

   
    bool G_code;

    float r_b;
    float h_b;

    float r_t;
    float h_t;
    float alfa;

    float x_t, y_t, z_t;
    float x_a_t, y_a_t, z_a_t;
    float x_b, y_b, z_b;
    int num_vert_b, num_vert_t;


    std::vector<float> t0;
    std::vector<float> t1;
    std::vector<float> t2;
    std::vector<float> t3;
    std::vector<float> t4;

    void get_inputs(GLFWwindow* window, Grid grid);
    float get_delTime();

};