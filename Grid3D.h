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
#include <execution>

class Grid3D
{
public:
	std::vector<glm::vec4> grid;
	std::vector<glm::vec4> grid_test;
	std::vector<glm::vec4> grid_draw;
	std::vector<std::vector<glm::vec2>> dexel_blank;
	
	glm::vec2* d_blank_pointer;
	int* num_of_dexels_pointer;
	glm::vec2* d_tool_pointer;
	glm::vec2** d_layers_blank_pointer;
	bool** d_layers_tool_pointer;
	glm::vec2* time_dexel_data;

	std::vector < glm::vec4> tool_dexel_cloud;
	std::vector < glm::vec2> tool_dexel_grid;

	glm::vec3 tool_min_rect;
	glm::vec3 tool_max_rect;

	glm::vec3 blank_min_rect;
	glm::vec3 blank_max_rect;

	float num_blank_dexels;

	glm::vec2 x_inters_d;
	glm::vec2 y_inters_d;


	float tool_dx;
	float tool_dy;
	float tool_dz;

	float tool_ax;
	float tool_ay;
	float tool_az;

	float tool_h;
	float tool_r;

	float offcenter = 50;

	std::vector<glm::vec2> dexel_tool;

	std::vector<glm::vec3> tool_grid;

	int X_blank_size, Y_blank_size, Z_blank_size;
	int X_tool_size, Y_tool_size, Z_tool_size;
	int X, Y, Z;

	void set_tool_offset(float dx, float dy, float dz, float ax, float ay, float az);
	void updateBbox();
	void get_intersection_size();
	void Boolean_op();


	glm::vec3 transform(glm::vec3 coord);
	glm::vec3 inv_transform(glm::vec3 coord);
	void get_tool_bbox();
	void create_blank_dexel_dyn(float r, float h);
	void create_blank_dexel(float r, float h);
	void create_tool_dexel_dyn(float r, float h, float dx, float dy, float dz, float ax, float ay, float az);

	void grid_dexel_draw_dyn();
	//bool Scalar_cyl(float r, float x, float y);


};

