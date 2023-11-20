#pragma once
#include <GLFW\glfw3.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

class Grid
{
public:
    std::vector<glm::vec3> grid;
    std::vector<glm::vec3> grid_draw;
    std::vector<int> voxel_id;
    std::vector<glm::vec3> grid_tool;
    std::vector<glm::vec3> grid_blank;
    std::vector<glm::vec3> tmp_vec;
    //std::vector<glm::vec4> dexels_blank;
    //std::vector<glm::vec4> dexels_tool;

    std::vector<glm::vec4> dexels_tool;
    std::vector<glm::vec4> dexels_blank;


    float x_tool=0;
    float y_tool;
    float z_tool;
    float a_tool;


    float x_blank_min;
    float y_blank_min;
    float z_blank_min;
    float x_blank_max;
    float y_blank_max;
    float z_blank_max;

    void create_draw_grid();
    bool scalar_cyl(float r, float x, float y);
    bool scalar_cyl_tool(float r, float x, float y);
    bool scalar_sphere(float r, float x, float y, float z);

    void create_cyl_dexel(int r, int h);

    void create_cyl(int r, int h);
    void create_cyl_dexels(int r, int h);
    void create_tool_dexels(int r, int h, float dx, float dy, float dz, float x_a, float y_a, float z_a);
    void draw_dexels();
    void create_tool(int r, int h, float dx, float dy, float dz, float x_a, float y_a, float z_a);
    void create_sphere(int r, float dx, float dy, float dz);
    void bolean_cut();
    


};

