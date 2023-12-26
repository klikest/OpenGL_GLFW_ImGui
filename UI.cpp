#include "UI.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW\glfw3.h>
#include <string>
#include <iostream>
#include "UI_Data.h"
#include "implot.h"

bool G_code_u = false;

int d_tool = 100;
int h_tool = 10;

int d_blank = 16;
int h_blank = 70;

int x_t=30, y_t=-90, z_t=0, a_x_t=0, a_y_t=0, a_z_t=0;

float grid_size = 1;

float get_grid_size()
{
	return grid_size;
}

void InitUI(GLFWwindow* window)
{
	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO&io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::StyleColorsDark();

	ImFont* font = io.Fonts->AddFontFromFileTTF("arial.ttf", 16.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	

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


bool get_G_code_bool()
{
	return G_code_u;
}

glm::vec3 get_coord_tool()
{
	float size = 1 / grid_size;

	return glm::vec3(x_t*size, y_t * size, z_t * size);
}

glm::vec3 get_angle_tool()
{
	return glm::vec3(a_x_t, a_y_t, a_z_t);
}

glm::vec4 get_tool_and_blank()
{
	float size = 1 / grid_size;
	return glm::vec4((d_tool/2)*size, h_tool*size, (d_blank/2)*size, h_blank*size);
}

void RenderUI(GLFWwindow* window, UI_Data data)
{
	int FPS = (int)(1 / data.delta_time);
	std::string FPS_s = "FPS =" + std::to_string(FPS);
	std::string cam_x = "Cavera X =" + std::to_string(data.camPos.x);
	std::string cam_y = "Cavera Y =" + std::to_string(data.camPos.y);
	std::string cam_z = "Cavera Z =" + std::to_string(data.camPos.z);
	std::string yaw = "Cavera Yaw =" + std::to_string(data.cam_yaw);
	std::string pitch = "Cavera Pitch =" + std::to_string(data.cam_pitch);
	std::string num_t = "Num tool dexels =" + std::to_string(data.num_vert_t);
	std::string num_b = "Num blank dexels =" + std::to_string(data.num_vert_b);
	std::string r = u8"Радиус инструмента =" + std::to_string(round(data.r_t));
	//std::string h = u8"Высота заготовки =" + std::to_string(data.h);


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	
	
	if (ImPlot::BeginPlot(u8"Графики времени выполнения операций")) {
		//ImPlot::PlotLine(u8"Подготовительные операции", data.t0.data(), data.t0.size());
		ImPlot::SetNextAxesToFit();
		ImPlot::PlotLine(u8"Генерация точек инструмента", data.t1.data(), data.t1.size());
		ImPlot::PlotLine(u8"Булева операция", data.t2.data(), data.t2.size());
		ImPlot::PlotLine(u8"Рендер моделей и интерфейса", data.t3.data(), data.t3.size());
		ImPlot::EndPlot();
	}


	ImGui::Begin("Info");
	ImGui::Text(FPS_s.c_str());

	ImGui::SliderFloat("Grid size", &grid_size, 0.1, 1);
	ImGui::Text("Blank");
	ImGui::SliderInt("D blank", &d_blank, 1.0f, 100.0f);
	ImGui::SliderInt("H blank", &h_blank, 1.0f, 500.0f);
	ImGui::Text("Tool");
	ImGui::SliderInt("D tool", &d_tool, 1, 200);
	ImGui::SliderInt("H tool", &h_tool, 1, 100);
	ImGui::SliderInt("X", &x_t, -200.0f, 200.0f);
	ImGui::SliderInt("Y", &y_t, -200.0f, 200.0f);
	ImGui::SliderInt("Z", &z_t, -200.0f, 200.0f);
	ImGui::SliderInt("A", &a_x_t, -180.0f, 180.0f);
	ImGui::SliderInt("B", &a_y_t, -180.0f, 180.0f);
	ImGui::SliderInt("C", &a_z_t, -180.0f, 180.0f);
	ImGui::Text("Calc info");
	ImGui::Text(num_t.c_str());
	ImGui::Text(num_b.c_str());
	//ImGui::Checkbox("123", &G_code_u);
	ImGui::Text(r.c_str());
	ImGui::Text(cam_x.c_str());
	ImGui::Text(cam_y.c_str());
	ImGui::Text(cam_z.c_str());
	ImGui::Text(yaw.c_str());
	ImGui::Text(pitch.c_str());
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