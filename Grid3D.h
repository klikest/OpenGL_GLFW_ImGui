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

class Grid3D
{
public:
	std::vector<glm::vec4> grid;
	std::vector<glm::vec4> grid_test;
	std::vector<glm::vec4> grid_draw;
	std::vector<std::vector<glm::vec2>> dexel_blank;
	glm::vec2* d_blank_pointer;
	std::vector<glm::vec2> dexel_tool;

	std::vector<glm::vec3> tool_grid;

	int X_blank_size, Y_blank_size, Z_blank_size;
	int X_tool_size, Y_tool_size, Z_tool_size;
	int X, Y, Z;

	void create_blank_dexel(float r, float h);
	void create_blank_dexel_dyn(float r, float h);
	void create_tool_dexel(float r, float h, float dx, float dy, float dz, float ax, float ay, float az);

	void fill_grid_blank(int x_size, int y_size, int z_size);
	void fill_grid_tool(int x_size, int y_size);
	void grid_dexel_draw();
	void grid_dexel_draw_dyn();
	void set_draw();
	void create_blank_grid(float r, float h);
	bool Scalar_cyl(float r, float x, float y);
	glm::vec4 get_vert_by_num(int i);
	int get_num_by_vert(glm::vec4 vertex);

};

