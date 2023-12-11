#include "Grid3D.h"
#include "thread"
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include "UI_Data.h"
#include <GLFW/glfw3.h>


bool Scalar_cyl(float r, float x, float y)
{
    if ((x * x) + (y * y) <= (r * r))
    {
        return true;
    }
    else
    {
        return false;
    }
}



glm::vec3 Grid3D::transform(glm::vec3 coord)
{
    glm::mat4 trans_y = glm::mat4(1.0f);
    trans_y = glm::rotate(trans_y, glm::radians(tool_ax), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec4 coords_ = trans_y * glm::vec4(coord.x, coord.y, coord.z, 1.0f);
    return glm::vec3(coords_.x, coords_.y, coords_.z);
}

glm::vec3 Grid3D::inv_transform(glm::vec3 coord)
{
    glm::mat4 trans_y = glm::mat4(1.0f);
    trans_y = glm::rotate(trans_y, -glm::radians(tool_ax), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec4 coords_ = trans_y * glm::vec4(coord.x, coord.y, coord.z, 1.0f);
    return glm::vec3(coords_.x, coords_.y, coords_.z);
}


void Grid3D::create_blank_dexel_dyn(float r, float h)
{
    bool start = true;
    if (X_blank_size != int((2 * r) + 10) || Z_blank_size != (int)h )
    {
        if (!start)
        {
            for (int i = 0; i < sizeof(d_layers_blank_pointer) / sizeof(glm::vec2); i++)
            {
                delete[] d_layers_blank_pointer[i];
                d_layers_blank_pointer[i] = nullptr;
            }

            delete[] d_layers_blank_pointer;
            d_layers_blank_pointer = nullptr;
        }




        X_blank_size = (2 * r)+10 ;
        Y_blank_size = (2 * r) + 10;
        //delete[] d_blank_pointer;
        //d_blank_pointer = nullptr;
        //d_blank_pointer = new glm::vec2[X_blank_size * Y_blank_size];
        

        d_layers_blank_pointer = new glm::vec2*[X_blank_size * Y_blank_size];


        Z_blank_size = h;

        X_blank_size = (2 * r) + 10;
        Y_blank_size = (2 * r) + 10;

        blank_min_rect = glm::vec3(-(r + 5), -(r + 5), 0);
        blank_max_rect = glm::vec3(r + 5, r + 5, h);
        
        std::vector<int> iter;
        iter.resize(X_blank_size * Y_blank_size);

        for (int i = 0; i < X_blank_size * Y_blank_size; i++)
        {
            iter[i] = i;
        }

        std::for_each(std::execution::par, iter.begin(), iter.end(),
            [this, r, h](int i)
            {
                d_layers_blank_pointer[i] = new glm::vec2[1];

                if (Scalar_cyl(r, i % X_blank_size - X_blank_size / 2, (i / X_blank_size) % Y_blank_size - Y_blank_size / 2))
                {
                    d_layers_blank_pointer[i][0] = glm::vec2(0, h);
                }
                else
                {
                    d_layers_blank_pointer[i][0] = glm::vec2(0, 0);
                }
            });

        start = false;

    }   

}


void Grid3D::get_intersection_size()
{

    //                 X

    //    -----------                   blank
    //                -----------       tool
    //               or
    //                -----------       blank
    //    -----------                   tool
    if (tool_min_rect.x > blank_max_rect.x || tool_max_rect.x < blank_min_rect.x) 
    { 
        x_inters_d = glm::vec2(0, 0); // X
    }
    
    //    -----------          blank
    //         --------------  tool
    else if (tool_min_rect.x > blank_min_rect.x && tool_min_rect.x < blank_max_rect.x && tool_max_rect.x > blank_max_rect.x)
    {
        x_inters_d = glm::vec2(tool_min_rect.x, blank_max_rect.x); // X
    }

    //    -------------        blank
    //       ------            tool
    else if (tool_min_rect.x > blank_min_rect.x && tool_min_rect.x < blank_max_rect.x && tool_max_rect.x < blank_max_rect.x)
    {
        x_inters_d = glm::vec2(tool_min_rect.x, tool_max_rect.x); // X
    }

    //         -----------     blank
    //    -----------          tool
    else if (blank_min_rect.x > tool_min_rect.x && blank_min_rect.x < tool_max_rect.x && blank_max_rect.x > tool_max_rect.x)
    {
        x_inters_d = glm::vec2(blank_min_rect.x, tool_max_rect.x); // X
    }

    //       -----             blank
    //    -----------          tool
    else if (blank_min_rect.x > tool_min_rect.x && blank_min_rect.x < tool_max_rect.x && blank_max_rect.x < tool_max_rect.x)
    {
        x_inters_d = glm::vec2(blank_min_rect.x, blank_max_rect.x); // X
    }

    //    -----------          blank
    //    -----------          tool
    else if (blank_min_rect.x == tool_min_rect.x && blank_max_rect.x == tool_max_rect.x)
    {
        x_inters_d = glm::vec2(blank_min_rect.x, blank_max_rect.x); // X
    }

    else
    {
        std::cout << "Error compute bbox boolean cut X" << std::endl;
    }



    // ---------------------------------------------------

    //               Y

    //    -----------                   blank
    //                -----------       tool
    //               or
    //                -----------       blank
    //    -----------                   tool
    if (tool_min_rect.y > blank_max_rect.y || tool_max_rect.y < blank_min_rect.y)
    {
        y_inters_d = glm::vec2(0, 0); // Y
    }

    //    -----------          blank
    //         --------------  tool
    else if (tool_min_rect.y > blank_min_rect.y && tool_min_rect.y < blank_max_rect.y && tool_max_rect.y > blank_max_rect.y)
    {
        y_inters_d = glm::vec2(tool_min_rect.y, blank_max_rect.y); // Y
    }

    //    -------------        blank
    //       ------            tool
    else if (tool_min_rect.y > blank_min_rect.y && tool_min_rect.y < blank_max_rect.y && tool_max_rect.y < blank_max_rect.y)
    {
        y_inters_d = glm::vec2(tool_min_rect.y, tool_max_rect.y); // Y
    }

    //         -----------     blank
    //    -----------          tool
    else if (blank_min_rect.y > tool_min_rect.y && blank_min_rect.y < tool_max_rect.y && blank_max_rect.y > tool_max_rect.y)
    {
        y_inters_d = glm::vec2(blank_min_rect.y, tool_max_rect.y); // Y
    }

    //       -----             blank
    //    -----------          tool
    else if (blank_min_rect.y > tool_min_rect.y && blank_min_rect.y < tool_max_rect.y && blank_max_rect.y < tool_max_rect.y)
    {
        y_inters_d = glm::vec2(blank_min_rect.y, blank_max_rect.y); // Y
    }

    //    -----------          blank
    //    -----------          tool
    else if (blank_min_rect.y == tool_min_rect.y && blank_max_rect.y == tool_max_rect.y)
    {
        y_inters_d = glm::vec2(blank_min_rect.y, blank_max_rect.y); // Y
    }

    else
    {
        std::cout << "Error compute bbox boolean cut Y" << std::endl;
    }


}


void Grid3D::set_tool_offset(float dx, float dy, float dz, float ax, float ay, float az)
{
    tool_dx = dx;
    tool_dy = dy;
    tool_dz = dz;

    tool_ax = ax;
    tool_ay = ay;
    tool_az = az;
}


void Grid3D::Boolean_op()
{
    get_intersection_size();

    int num_x_intersection_dexels = x_inters_d.y - x_inters_d.x;
    int num_y_intersection_dexels = y_inters_d.y - y_inters_d.x;
    
    int num_inters = num_x_intersection_dexels * num_y_intersection_dexels;

    std::vector<int> iter_blank_mass;
    std::vector<int> iter_tool_mass;

    int len_x = x_inters_d.y - x_inters_d.x;
    int len_y = y_inters_d.y - y_inters_d.x;

    int num_x_start_blank = x_inters_d.x - blank_min_rect.x;
    int num_y_start_blank = y_inters_d.x - blank_min_rect.y;
    int i_start_blank = num_x_start_blank + X_blank_size * num_y_start_blank;

    for (int i = 0; i < len_y; i++)
    {
        int iter_blank = i_start_blank + X_blank_size * i;

        for (int j = 0; j < len_x; j++)
        {
            iter_blank_mass.push_back(iter_blank);
            iter_blank += 1;
        }    
    }

    int num_x_start_tool = x_inters_d.x - tool_min_rect.x;
    int num_y_start_tool = y_inters_d.x - tool_min_rect.y;
    int i_start_tool = num_x_start_tool + X_tool_size * num_y_start_tool;

    for (int i = 0; i < len_y; i++)
    {
        int iter_tool = i_start_tool + X_tool_size * i;

        for (int j = 0; j < len_x; j++)
        {
            iter_tool_mass.push_back(iter_tool);
            iter_tool += 1;
        }
    }


    for (int i = 0; i < iter_blank_mass.size(); i++)
    {

        for (int l_num_of_dexel = 0; l_num_of_dexel < sizeof(d_layers_blank_pointer[iter_blank_mass[i]])/sizeof(glm::vec2); l_num_of_dexel++)
        {
            if (tool_dexel_grid[iter_tool_mass[i]].y != 0 && d_layers_blank_pointer[iter_blank_mass[i]][l_num_of_dexel].y != 0 && d_layers_blank_pointer[iter_blank_mass[i]][l_num_of_dexel].y > tool_min_rect.z + tool_dexel_grid[iter_tool_mass[i]].x)
            {
                if (tool_min_rect.z + tool_dexel_grid[iter_tool_mass[i]].x <= 0)
                {
                    d_layers_blank_pointer[iter_blank_mass[i]][l_num_of_dexel].y = 0;
                }
                else
                {
                    d_layers_blank_pointer[iter_blank_mass[i]][l_num_of_dexel].y = tool_min_rect.z + tool_dexel_grid[iter_tool_mass[i]].x;
                }
            }
        }

    }


    //std::cout << iter_tool_mass[0] << std::endl;

    //std::cout << "X0 = " << x_inters_d.x << " X1 = " << x_inters_d.y << std::endl;
    //std::cout << "Y0 = " << y_inters_d.x << " Y1 = " << y_inters_d.y << std::endl;
    //std::cout << " " << std::endl;
 }



void Grid3D::updateBbox()
{
    //tool_min_rect.x -= 0.5;
    //tool_min_rect.y -= 0.5;
    
    //tool_max_rect.x += 0.5;
    //tool_max_rect.y += 0.5;
    //tool_max_rect.z += 1;
}

void Grid3D::get_tool_bbox()
{
    tool_min_rect = glm::vec3(1000000, 1000000, 1000000);
    tool_max_rect = glm::vec3(-1000000, -1000000, -1000000);

    for (float i = 0; i < 6.3; i += 0.2)
    {
        glm::vec3 coords_0 = glm::vec3(tool_r * sin(i), tool_r * cos(i), 0);


        glm::vec3 new_point = transform(coords_0);

        if (tool_min_rect.x > new_point.x) { tool_min_rect.x = new_point.x; }
        if (tool_max_rect.x < new_point.x) { tool_max_rect.x = new_point.x; }
        if (tool_min_rect.y > new_point.y) { tool_min_rect.y = new_point.y; }
        if (tool_max_rect.y < new_point.y) { tool_max_rect.y = new_point.y; }
        if (tool_min_rect.z > new_point.z) { tool_min_rect.z = new_point.z; }
        if (tool_max_rect.z < new_point.z) { tool_max_rect.z = new_point.z; }
    }

    for (float i = 0; i < 6.3; i += 0.2)
    {
        glm::vec3 coords_0 = glm::vec3(tool_r * sin(i), tool_r * cos(i), tool_h);

        glm::vec3 new_point = transform(coords_0);

        if (tool_min_rect.x > new_point.x) { tool_min_rect.x = new_point.x; }
        if (tool_max_rect.x < new_point.x) { tool_max_rect.x = new_point.x; }
        if (tool_min_rect.y > new_point.y) { tool_min_rect.y = new_point.y; }
        if (tool_max_rect.y < new_point.y) { tool_max_rect.y = new_point.y; }
        if (tool_min_rect.z > new_point.z) { tool_min_rect.z = new_point.z; }
        if (tool_max_rect.z < new_point.z) { tool_max_rect.z = new_point.z; }
    }


    //tool_min_rect.x -= 1;
    //tool_min_rect.y -= 1;

    //tool_max_rect.x += 1;
    //tool_max_rect.y += 1;


    X_tool_size = tool_max_rect.x - tool_min_rect.x;
    Y_tool_size = tool_max_rect.y - tool_min_rect.y;
    Z_tool_size = tool_max_rect.z - tool_min_rect.z;
}

void Grid3D::create_tool_dexel_dyn(float r, float h, float dx, float dy, float dz, float ax, float ay, float az)
{
    set_tool_offset(dx, dy, dz, ax, ay, az);
    tool_r = r;
    tool_h = h;

    get_tool_bbox();



    //d_layers_tool_pointer = new bool* [X_tool_size * Y_tool_size];

    //for (int i = 0; i < sizeof(d_layers_tool_pointer) / sizeof(bool); i++)
    //{
    //    if (d_layers_tool_pointer != nullptr)
    //    {
            //delete[] d_layers_tool_pointer[i];
            //d_layers_tool_pointer[i] = nullptr;
    //    }
    //}
    //delete[] d_layers_tool_pointer;
    //d_layers_tool_pointer = nullptr;


    std::vector<std::vector<bool>> test;

    tool_grid.clear();

    for (int n = 0; n < X_tool_size * Y_tool_size; n++)
    {
        std::vector<bool> layer;
        layer.clear();

        for (int z = 0; z < Z_tool_size; z++)
        {
            float curr_x = n % X_tool_size  + tool_min_rect.x;
            float curr_y = (n / X_tool_size) % Y_tool_size  + tool_min_rect.y;
            float curr_z = z + tool_min_rect.z;

            glm::vec3 point = glm::vec4(curr_x, curr_y, curr_z, 1.0f);

            glm::vec3 old_point = inv_transform(point);
           

            //std::cout << "X = " << coords___.x << std::endl;
            //std::cout << "Y = " << coords___.y << std::endl;
            //std::cout << "Z = " << coords___.z << std::endl;
            //std::cout << " " << std::endl;

            if (Scalar_cyl(tool_r, old_point.x, old_point.y) && old_point.z >= 0 && old_point.z <= tool_h)
            {
                layer.push_back(true);
                tool_grid.push_back(point);
            }
            else
            {
                layer.push_back(false);
            }


        }
        test.push_back(layer);
    }

    delete[] d_tool_pointer;
    d_tool_pointer = nullptr;
    d_tool_pointer = new glm::vec2[X_tool_size * Y_tool_size];


    for (int n = 0; n < X_tool_size * Y_tool_size; n++)
    {
        int z0 = 0;
        int z1 = 0;

        int z = 0;

        for (int i = 0; i < Z_tool_size; i++)
        {
            if (test[n][i])
            {
                z0 = i;
                i += Z_tool_size;
            }
        }

        for (int i = Z_tool_size; i << Z_tool_size >  0; i--)
        {
            if (test[n][i])
            {
                z1 = i;
                i -= Z_tool_size;
            }
        }

        d_tool_pointer[n] = glm::vec2(z0, z1-z0);

    }

}



void Grid3D::grid_dexel_draw_dyn()
{
    grid_draw.clear();
    
    for (int j = 0; j < X_blank_size * Y_blank_size; j++)
    {   /*
        if (d_blank_pointer[j].y != 0)
        {
            if ( (j> X_blank_size && j <(X_blank_size * Y_blank_size)- X_blank_size)
                &&
                d_blank_pointer[j + 1].y != 0
                &&
                d_blank_pointer[j - 1].y != 0
                &&
                d_blank_pointer[j + X_blank_size].y != 0
                &&
                d_blank_pointer[j - X_blank_size].y != 0)
            {
                grid_draw.push_back(glm::vec4(j % X_blank_size - X_blank_size / 2, (j / X_blank_size) % Y_blank_size - Y_blank_size / 2, d_blank_pointer[j].x, 1));
                grid_draw.push_back(glm::vec4(j % X_blank_size - X_blank_size / 2, (j / X_blank_size) % Y_blank_size - Y_blank_size / 2, d_blank_pointer[j].y-1, 1));
            }
            else
            {
                grid_draw.push_back(glm::vec4(j % X_blank_size - X_blank_size / 2, (j / X_blank_size) % Y_blank_size - Y_blank_size / 2, d_blank_pointer[j].x, d_blank_pointer[j].y));
            }

        }
        */
        for (int num = 0; num < sizeof(d_layers_blank_pointer[j]) / sizeof(glm::vec2); num++)
        {
            if (d_layers_blank_pointer[j][num].y != 0)
            {
                //grid_draw.push_back(glm::vec4(j % X_blank_size - X_blank_size / 2, (j / X_blank_size) % Y_blank_size - Y_blank_size / 2, d_layers_blank_pointer[j][num].x, d_layers_blank_pointer[j][num].y));
            }
        }
    }

    for (int j = 0; j < X_tool_size * Y_tool_size; j++)
    {  

        if (d_tool_pointer[j].y != 0)
        {
            //grid_draw.push_back(glm::vec4(j % X_tool_size + tool_min_rect.x + 0.5, (j / X_tool_size) % Y_tool_size + tool_min_rect.y + 0.5, d_tool_pointer[j].x + tool_min_rect.z, d_tool_pointer[j].y));
        }
    }


    for (int i = 0; i < tool_grid.size(); i++)
    {
        grid_draw.push_back(glm::vec4(tool_grid[i], 1));
    }

}









