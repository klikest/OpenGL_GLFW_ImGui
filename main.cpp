
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
#include "Grid.h"

using namespace std;

#define numVAOs 2
#define numVBOs 5

//Utils util = Utils();
float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
GLuint renderingProgram, renderingProgram_coords;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

int displayLoopi;

glm::mat4 tMat, rMat, mMat, mvMat;


GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;



int r = 5, h = 5;
int r_t = 1, h_t = 1;


string prog_0 = "G1 X0; G1 Y0; G1 Z0";

/*
std::vector<glm::vec3> G_code_run(Grid grid, string prog)
{
    string curret_command = "";

    float x_new, y_new, z_new, a_new;
    string x_new_s = "", y_new_s = "", z_new_s = "", a_new_s="";

    int sym_num = 0;

    std::vector<glm::vec3> coords;

    while (sym_num < prog.size())
    {
        if (prog[sym_num] == 'G')
        {
            curret_command = "G" + prog[sym_num+1];
            sym_num += 2;

            while (sym_num < prog.size() || prog[sym_num] != ';')
            {
                if (prog[sym_num] == 'X')
                {
                    sym_num += 1;

                    while (prog[sym_num] != ' ')
                    {
                        x_new_s += prog[sym_num];
                        sym_num += 1;
                    }
                }
                if (prog[sym_num] == 'Y')
                {
                    sym_num += 1;

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

                    while (prog[sym_num] != ' ')
                    {
                        z_new_s += prog[sym_num];
                        sym_num += 1;
                    }
                }
                if (prog[sym_num] == 'A')
                {
                    sym_num += 1;

                    while (prog[sym_num] != ' ')
                    {
                        a_new_s += prog[sym_num];
                        sym_num += 1;
                    }
                }

            }

            x_new = std::stof(x_new_s);
            y_new = std::stof(y_new_s);
            z_new = std::stof(z_new_s);
            a_new = std::stof(a_new_s);

            float x_old = grid.x_tool;
            float y_old = grid.y_tool;
            float z_old = grid.z_tool;
            float a_old = grid.a_tool;

            float dx = abs(x_new - x_old);
            float dy = abs(y_new - y_old);
            float dz = abs(z_new - z_old);
            float da_a = abs(a_new - a_old);

            float d = min(dx, dy, dz);




        }
        sym_num += 1;

    }
    return coords;
}
*/




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









void setupVertices(void) {
    // 12 triangles * 3 vertices * 3 values (x, y, z)
    float vertexPositions[108] = {
        -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,
         0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f,
    };

    
    Grid grid;
    //grid.create_cyl(r, h);
    //grid.create_sphere(10, 100, 0, 0);
    glGenVertexArrays(2, vao);  // creates VAO and returns the integer ID
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

    float l = 60;
    float dl = l / 30;
    float d = l - dl;
    

    float line[] = {
    0.0, 0.0, 0.0,
    l, 0.0, 0.0,
    l, 0.0, 0.0,
    d, 0.0, dl,
    l, 0.0, 0.0,
    d, 0.0, -dl,

    0.0, 0.0, 0.0,
    0.0, l, 0.0,
    0.0, l, 0.0,
    0.0, d, dl,
    0.0, l, 0.0,
    0.0, d, -dl,

    0.0, 0.0, 0.0,
    0.0, 0.0, l,
    0.0, 0.0, l,
    0.0, dl, d,
    0.0, 0.0, l,
    0.0, -dl, d
    };
    float color[] = {
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,

    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,

    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0
    };

     // creates VAO and returns the integer ID
    glBindVertexArray(vao[1]);
    glEnableVertexAttribArray(0);// creates VBO and returns the integer ID
    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


}

// once
void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram((char*)"vert_shader.glsl", (char*)"frag_shader.glsl");
    renderingProgram_coords = createShaderProgram((char*)"coords_vert.glsl", (char*)"coords_frag.glsl");

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

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, grid.grid_draw.size());


    
    glUseProgram(renderingProgram_coords);
    glEnableVertexAttribArray(0);// creates VBO and returns the integer ID
    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnable(GL_LINE_SMOOTH);
    glDrawArrays(GL_LINES, 0, 6*3);
    

}



int main(void) {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwSwapInterval(1);
    GLFWwindow* window = glfwCreateWindow(900, 600, "Voxel Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }

    // GLFW Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    init(window);
    InitUI(window);
    
    Camera camera(window, glm::vec3(-10.0f, 10.0f, 20.0f), -62, -25);


    camera.cameraPos = glm::vec3(-64, 92, 100);
    camera.cam_speed = 100;


    UI_Data data;


    data.r_b = 40;
    data.h_b = 1;
    data.r_t = 50;

    Grid grid;
    grid.create_cyl(data.r_b, data.h_b);
    

    data.x_t = -100;
    data.y_t = 62;
    data.z_t = 10;
    data.alfa = 3.14/2;
    data.h_t = 20;
    
    grid.create_tool(data.r_t, 10, data.x_t, data.y_t, data.z_t, data.alfa, 0, 0);

    float rad = 5;

    int steps_prog = 0;

    std::vector<glm::vec3> coords_tool;
    std::vector<glm::vec3> angles_tool;

    for (int i = 0; i < 100; i++)
    {
        float x_min = -50;
        float x_max = 10;
        float alfa_min = 0;
        float alfa_max = 3.14;
        
        float dx = (x_max - x_min) / 100;
        float dalfa = (alfa_max - alfa_min) / 100;



        coords_tool.push_back(glm::vec3(-100 + i*dx, 0, 0));
        angles_tool.push_back(glm::vec3(i*dalfa, 0, 0));
    }

    while (!glfwWindowShouldClose(window)) {

        data.G_code = get_G_code_bool();
        
        if (data.G_code)
        {
            while (steps_prog < coords_tool.size())
            {
            data.num_vert_b = grid.grid_blank.size();
            data.num_vert_t = grid.grid_tool.size();
            data.cam_yaw = camera.yaw;
            data.cam_pitch = camera.pitch;

            float t_1 = (GLfloat)glfwGetTime();

            grid.create_tool(data.r_t, data.h_t, coords_tool[steps_prog].x, coords_tool[steps_prog].y, coords_tool[steps_prog].z, angles_tool[steps_prog].x, 0, 0);
            steps_prog += 1;

            float t_2 = (GLfloat)glfwGetTime();


            grid.bolean_cut();


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
            camera.UpdateMatrix(renderingProgram, renderingProgram_coords);
            glfwSwapBuffers(window);
            glfwPollEvents();
            float t_0 = (GLfloat)glfwGetTime();

            data.t1 = add_data_to_plot(data.t1, (t_2 - t_1));
            data.t2 = add_data_to_plot(data.t2, (t_3 - t_2));
            data.t3 = add_data_to_plot(data.t3, (t_0 - t_3));
            }

            steps_prog = 0;
         

        }
        else
        {

            data.x_t = get_coord_tool().x;
            data.y_t = get_coord_tool().y;
            data.z_t = get_coord_tool().z;

            data.x_a_t = get_angle_tool().x;
            data.y_a_t = get_angle_tool().y;
            data.z_a_t = get_angle_tool().z;

            //data.get_inputs(window, grid);

            data.num_vert_b = grid.grid_blank.size();
            data.num_vert_t = grid.grid_tool.size();
            data.cam_yaw = camera.yaw;
            data.cam_pitch = camera.pitch;

            float t_1 = (GLfloat)glfwGetTime();

            grid.create_tool(data.r_t, data.h_t, data.x_t, data.y_t, data.z_t, data.x_a_t, data.y_a_t, data.z_a_t);


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
            camera.UpdateMatrix(renderingProgram, renderingProgram_coords);
            glfwSwapBuffers(window);
            glfwPollEvents();
            float t_0 = (GLfloat)glfwGetTime();

            //data.t0 = add_data_to_plot(data.t0, (t_1 - t_0));
            data.t1 = add_data_to_plot(data.t1, (t_2 - t_1));
            data.t2 = add_data_to_plot(data.t2, (t_3 - t_2));
            data.t3 = add_data_to_plot(data.t3, (t_0 - t_3));
        }
        
    }

    ImGui::DestroyContext();
    ImPlot::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}