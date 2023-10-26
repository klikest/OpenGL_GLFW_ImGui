
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include "Utils.h"
#include "Camera.h"
#include "UI.h"
#include "UI_Data.h"

using namespace std;

#define numVAOs 1
#define numVBOs 3

//Utils util = Utils();
float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

int displayLoopi;

glm::mat4 tMat, rMat, mMat, mvMat;


GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;



int r = 5, h = 5;
int r_t = 1, h_t = 1;



std::vector<float> add_data_to_plot(std::vector<float> data, float new_data)
{
    if (data.size() < 500)
    {
        data.push_back(new_data);
    }
    else
    {
        data.erase(data.begin());
        data.push_back(new_data);
    }

    return data;
}




bool scalar_cyl(float r, float x, float y)
{
    if ((x * x) + (y * y) < (r * r))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool scalar_sphere(float r, float x, float y, float z)
{
    if ((x * x) + (y * y) + (z * z) > (r * r)-0.1*(r * r) && (x * x) + (y * y) + (z * z) < (r * r))
    {
        return true;
    }
    else
    {
        return false;
    }
}


struct Grid
{
    std::vector<glm::vec3> grid;
    std::vector<glm::vec3> grid_draw;
    std::vector<int> voxel_id;
    std::vector<glm::vec3> grid_tool;
    std::vector<glm::vec3> grid_blank;


    void create_cyl(int r, int h)
    {
        grid_blank.clear();
        for (int i = 0; i < h; i++)
        {
            for (int j = -r; j < r; j++)
            {
                    for (int k =-r; k < r; k++)
                    {
                        if (scalar_cyl(r, j, k))
                        {
                            grid_blank.push_back(glm::vec3(i * 2, j * 2, -k * 2));
                        }
                     
                    }
            }
        }

    }

    void create_sphere(int r, float dx, float dy, float dz)
    {
        grid_tool.clear();
        for (int i = -r; i < r; i++)
        {
            for (int j = -r; j < r; j++)
            {
                for (int k = -r; k < r; k++)
                {
                    if (scalar_sphere(r, i, j, k))
                    {
                        //grid.push_back(glm::vec3(i * 2 + dx, j * 2 + dy, -k * 2 + dz));
                        //voxel_id.push_back(1);
                        grid_tool.push_back(glm::vec3(i * 2 + dx, j * 2 + dy, -k * 2 + dz));
                    }
                    else
                    {
                        //grid.push_back(glm::vec3(i * 2 + dx, j * 2 + dy, -k * 2 + dz));
                        //voxel_id.push_back(0);
                    }

                }

            }
        }

    }

    void bolean_cut()
    {
        grid_draw.clear();


        for (int i = 0; i < grid_blank.size(); i++)
        {
            for (int j = 0; j < grid_tool.size(); j++)
            {
                if (grid_tool[j]==grid_blank[i])
                {
                    //grid_blank.erase(std::remove(grid_blank.begin(), grid_blank.end(), grid_blank[i]), grid_blank.end());
                    grid_blank[i] = glm::vec3(1000, 1000, 1000);
                }

            }
        }

        for (int i = 0; i < grid_blank.size(); i++)
        {
            grid_draw.push_back(grid_blank[i]);
        }

        for (int j = 0; j < grid_tool.size(); j++)
        {
            grid_draw.push_back(grid_tool[j]);
        }

    }


    void create_draw_grid()
    {
        grid_draw.clear();
        for (int i = 0; i < grid_blank.size(); i++)
        {
            grid_draw.push_back(grid_blank[i]);
        }

        for (int j = 0; j < grid_tool.size(); j++)
        {
            grid_draw.push_back(grid_tool[j]);
        }
    }



};


void setupVertices(void) {
    // 12 triangles * 3 vertices * 3 values (x, y, z)
    float vertexPositions[108] = {
        -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,
    };

    
    Grid grid;
    //grid.create_cyl(r, h);
    //grid.create_sphere(10, 100, 0, 0);
    glGenVertexArrays(1, vao);  // creates VAO and returns the integer ID
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);  // creates VBO and returns the integer ID
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    // loads the cube vertices into the 0th VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * grid.grid_draw.size(), grid.grid_draw.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * grid.voxel_id.size(), grid.voxel_id.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(int), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// once
void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram((char*)"vert_shader.glsl", (char*)"frag_shader.glsl");

    setupVertices();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

}


// repeatedly
void display(GLFWwindow* window, double currentTime, Grid grid) {

    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * grid.grid_draw.size(), grid.grid_draw.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * grid.voxel_id.size(), grid.voxel_id.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(int), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, grid.grid_draw.size());
}



int main(void) {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwSwapInterval(1);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Voxel Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }

    // GLFW Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    init(window);
    InitUI(window);
    
    Camera camera(window, glm::vec3(-10.0f, 10.0f, 20.0f));

    Grid grid;
    grid.create_cyl(20, 10);


    UI_Data data;
    camera.cam_speed = 100;

    float x_t = -20;
    float y_t = 0;
    float z_t = 0;

    float rad = 5;


    while (!glfwWindowShouldClose(window)) {

        
        

        if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS) { x_t += 2; }
        if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS) { x_t -= 2; }
        if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS) { z_t += 2; }
        if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS) { z_t -= 2; }
        if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS) { y_t += 2; }
        if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS) { y_t -= 2; }
        if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS) { rad += 1; }
        if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS) { rad -= 1; }
        

        data.x_t = x_t;
        data.y_t = y_t;
        data.z_t = z_t;

        data.num_vert_b = grid.grid_blank.size();
        data.num_vert_t = grid.grid_tool.size();

        data.r_t = rad;

        float t_1 = (GLfloat)glfwGetTime();
        

        grid.create_sphere(rad, x_t, z_t, y_t);

        float t_2 = (GLfloat)glfwGetTime();
        

        grid.bolean_cut();
        //grid.create_draw_grid();

        float t_3 = (GLfloat)glfwGetTime();
        

        data.camPos = camera.cameraPos;
        data.cam_speed = camera.cam_speed;
        data.cam_pitch = camera.pitch;
        data.cam_yaw = camera.yaw;

        GLfloat currentFrame = (GLfloat)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        data.delta_time = deltaTime;
        display(window, glfwGetTime(), grid);
        RenderUI(window, data);
        camera.MoveCamera(window, deltaTime);
        camera.UpdateMatrix(renderingProgram);
        glfwSwapBuffers(window);
        glfwPollEvents();
        float t_0 = (GLfloat)glfwGetTime();

        //data.t0 = add_data_to_plot(data.t0, (t_1 - t_0));
        data.t1 = add_data_to_plot(data.t1, (t_2 - t_1));
        data.t2 = add_data_to_plot(data.t2, (t_3 - t_2));
        data.t3 = add_data_to_plot(data.t3, (t_0 - t_3));



    }

    ImGui::DestroyContext();
    ImPlot::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}