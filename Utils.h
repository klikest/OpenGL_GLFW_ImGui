#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

std::string readShaderSource(const char* filePath);
void printShaderLog(GLuint shader);
void printProgramLog(int prog);
bool checkOpenGLError();
GLuint createShaderProgram(char* vert, char* frag);

