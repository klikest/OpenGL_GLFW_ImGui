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
	std::vector<std::vector<glm::vec2>> dexel_tool;


	int X_blank_size, Y_blank_size, Z_blank_size;
	int X_tool_size, Y_tool_size, Z_tool_size;
	int X, Y, Z;

	void create_blank_dexel(float r, float h);

	void fill_grid(int x_size, int y_size, int z_size);
	void grid_dexel_draw();
	void set_draw();
	void create_blank_grid(float r, float h);
	bool Scalar_cyl(float r, float x, float y);
	glm::vec4 get_vert_by_num(int i);
	int get_num_by_vert(glm::vec4 vertex);

};

