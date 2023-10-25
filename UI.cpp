#include "UI.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW\glfw3.h>
#include <string>
#include <iostream>
#include "UI_Data.h"



void InitUI(GLFWwindow* window)
{
	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO&io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::StyleColorsDark();

	ImFont* font = io.Fonts->AddFontFromFileTTF("arial.ttf", 20.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");

}

void RenderUI(GLFWwindow* window, UI_Data data)
{
	int FPS = (int)(1 / data.delta_time);
	std::string FPS_s = "FPS =" + std::to_string(FPS);
	std::string cam_x = "Camera X =" + std::to_string(data.camPos.x);
	std::string cam_y = "Camera Y =" + std::to_string(data.camPos.y);
	std::string cam_z = "Camera Z =" + std::to_string(data.camPos.z);
	std::string cam_yaw = "Camera yaw =" + std::to_string(data.cam_yaw);
	std::string cam_pitch = "Camera pitch =" + std::to_string(data.cam_pitch);

	std::string r = u8"Радиус загатовки=" + std::to_string(round(data.r));
	std::string h = u8"Высота заготовки =" + std::to_string(data.h);


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Info");
	ImGui::Text(FPS_s.c_str());
	ImGui::Text(cam_x.c_str());
	ImGui::Text(cam_y.c_str());
	ImGui::Text(cam_z.c_str());
	ImGui::Text(cam_pitch.c_str());
	ImGui::Text(cam_yaw.c_str());
	ImGui::Text(r.c_str());
	ImGui::Text(h.c_str());
	//ImGui::ShowDemoWindow();
	ImGui::End();
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());;

	GLFWwindow* backup_current_context = glfwGetCurrentContext();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	glfwMakeContextCurrent(backup_current_context);


}