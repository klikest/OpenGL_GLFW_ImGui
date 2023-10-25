#pragma once
#include "UI.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW\glfw3.h>
#include "UI_Data.h"



void InitUI(GLFWwindow* window);
void RenderUI(GLFWwindow* window, UI_Data data);

