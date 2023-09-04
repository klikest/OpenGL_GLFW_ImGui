#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "UI.h"
#include "FrameBuffer.h"


using namespace std;




string readShaderSource(const char* filePath) {
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}



#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint createShaderProgram() {

	string vertShaderStr = readShaderSource("vert_shader.glsl");
	string fragShaderStr = readShaderSource("frag_shader.glsl");
	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();
	
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(vShader, 1, &vertShaderSrc, NULL);
	glShaderSource(fShader, 1, &fragShaderSrc, NULL);
	glCompileShader(vShader);
	glCompileShader(fShader);
	
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
	return vfProgram;
}
void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}


void display(GLFWwindow* window, double currentTime) {
	glfwPollEvents();
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	
	glUseProgram(renderingProgram);
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset"); // get ptr to "offset"
	glProgramUniform1f(renderingProgram, offsetLoc, 0); // send value in "x" to "offset"
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//RenderUI(window);
}

int main(void) {
	if (!glfwInit()) {  }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
	if (window == nullptr)
		return 1;

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {  }
	glfwSwapInterval(1);
	
	init(window);
	InitUI(window);


	float width = 600;
	float height = 300;

	FrameBuffer sceneBuffer(width, height);
	

	while (!glfwWindowShouldClose(window)) {
		
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ImGui::NewFrame();
		ImGui::Begin("Scene");
		{
			ImGui::BeginChild("GameRender");

			const float window_width = ImGui::GetContentRegionAvail().x;
			const float window_height = ImGui::GetContentRegionAvail().y;

			sceneBuffer.RescaleFrameBuffer(window_width, window_height);

			ImVec2 pos = ImGui::GetCursorScreenPos();

			ImGui::GetWindowDrawList()->AddImage(
				(void*)sceneBuffer.getFrameTexture(),
				ImVec2(pos.x, pos.y),
				ImVec2(pos.x + window_width, pos.y + window_height),
				ImVec2(0, 1),
				ImVec2(1, 0)
			);
		}
		ImGui::EndChild();
		ImGui::End();
		ImGui::Render();

		sceneBuffer.Bind();

		glUseProgram(renderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		sceneBuffer.Unbind();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);

		glfwSwapBuffers(window);

	}
	
	glfwDestroyWindow(window);
	

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();


}