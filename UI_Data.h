#pragma once
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

class UI_Data
{
public:
    glm::vec3 camPos;
    float cam_yaw;
    float cam_pitch;
    float cam_speed;
    float delta_time;

    float r;
    float h;

    float get_delTime();

};