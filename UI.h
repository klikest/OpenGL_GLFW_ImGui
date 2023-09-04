#pragma once
#include "UI.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW\glfw3.h>

void InitUI(GLFWwindow* window);
void RenderUI(GLFWwindow* window);

