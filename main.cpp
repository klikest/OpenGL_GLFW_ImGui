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
#include <cmath>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>
#include "UI.h"
#include "FrameBuffer.h"
#include "Utils.h"


using namespace std;


#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];

void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}


void display(GLFWwindow* window, double currentTime) {
	glfwPollEvents();
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	RenderUI(window);
	glfwSwapBuffers(window);
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

	
	while (!glfwWindowShouldClose(window)) {
		
		display(window, glfwGetTime());

	}
	
	glfwDestroyWindow(window);
	

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();


}