#pragma once
#include "UI.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW\glfw3.h>
#include "UI_Data.h"
#include "implot.h"



void InitUI(GLFWwindow* window);
void RenderUI(GLFWwindow* window, UI_Data data);
bool get_G_code_bool();
glm::vec3 get_coord_tool();
glm::vec3 get_angle_tool();

