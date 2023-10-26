#pragma once
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

class UI_Data
{
public:
    glm::vec3 camPos;
    float cam_yaw;
    float cam_pitch;
    float cam_speed;
    float delta_time;

    float r_b;
    float h_b;

    float r_t;

    float x_t, y_t, z_t;
    float x_b, y_b, z_b;
    int num_vert_b, num_vert_t;


    std::vector<float> t0;
    std::vector<float> t1;
    std::vector<float> t2;
    std::vector<float> t3;
    std::vector<float> t4;



    float get_delTime();

};