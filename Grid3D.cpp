#include "Grid3D.h"
#include "thread"
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include "UI_Data.h"


void Grid3D::create_blank_dexel_dyn(float r, float h)
{
    if (X_blank_size != 2 * r && Y_blank_size != 2 * r)
    {
        X_blank_size = (2 * r)+10 ;
        Y_blank_size = (2 * r) + 10;
        delete[] d_blank_pointer;
        d_blank_pointer = nullptr;
        d_blank_pointer = new glm::vec2[X_blank_size * Y_blank_size];
    }
    X_blank_size = (2 * r) + 10;
    Y_blank_size = (2 * r) + 10;

    std::vector<int> iter;
    iter.resize(X_blank_size * Y_blank_size);
    for (int i = 0; i < X_blank_size * Y_blank_size; i++)
        iter[i] = i;

    std::for_each(std::execution::par, iter.begin(), iter.end(),
        [this, r, h](int i)
        {
            if (Scalar_cyl(r, i % X_blank_size - X_blank_size / 2, (i / X_blank_size) % Y_blank_size - Y_blank_size / 2))
            {
                d_blank_pointer[i].y = h;
                d_blank_pointer[i].x = 0;
            }
            else
            {
                d_blank_pointer[i].y = 0;
                d_blank_pointer[i].x = 0;
            }
        });


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

}



void Grid3D::updateBbox()
{
    tool_min_rect.x -= 0.5;
    tool_min_rect.y -= 0.5;
    
    tool_max_rect.x += 0.5;
    tool_max_rect.y += 0.5;
    tool_max_rect.z += 1;
}



void Grid3D::create_tool_dexel_dyn(float r, float h, float dx, float dy, float dz, float ax, float ay, float az)
{

    tool_min_rect = glm::vec3(1000000, 1000000, 1000000);
    tool_max_rect = glm::vec3(-1000000, -1000000, -1000000);


    set_tool_offset(dx, dy, dz, ax, ay, az);

    tool_grid.clear();


    for (float i = -r; i <= r; i += 0.5)
    {
        for (float j = -r; j <= r; j += 0.5)
        {
            for (float k = 0; k < h; k += 0.5)
            {
                if (Scalar_cyl(r, i, j))
                {

                    glm::vec4 coords_0 = glm::vec4(i, j, k, 1.0f);

                    glm::mat4 trans_y = glm::mat4(1.0f);
                    trans_y = glm::rotate(trans_y, glm::radians(ax), glm::vec3(1.0f, 0.0f, 0.0f));
                    glm::vec4 coords__ = trans_y * glm::vec4(coords_0.x, coords_0.y, coords_0.z, 1.0f);

                    glm::mat4 trans_x = glm::mat4(1.0f);
                    trans_x = glm::rotate(trans_x, glm::radians(ay), glm::vec3(0.0f, 1.0f, 0.0f));
                    glm::vec4 coords_ = trans_x * coords__;

                    glm::mat4 trans_z = glm::mat4(1.0f);
                    trans_z = glm::rotate(trans_z, glm::radians(az), glm::vec3(0.0f, 0.0f, 1.0f));
                    glm::vec4 coords = trans_z * (coords_ + glm::vec4(dx, dy, dz, 0));



                    glm::vec3 new_point = glm::vec3(round(coords.x), round(coords.y), round(coords.z ));



                    if (tool_min_rect.x > new_point.x) { tool_min_rect.x = new_point.x; }
                    if (tool_max_rect.x < new_point.x) { tool_max_rect.x = new_point.x; }
                    if (tool_min_rect.y > new_point.y) { tool_min_rect.y = new_point.y; }
                    if (tool_max_rect.y < new_point.y) { tool_max_rect.y = new_point.y; }
                    if (tool_min_rect.z > new_point.z) { tool_min_rect.z = new_point.z; }
                    if (tool_max_rect.z < new_point.z) { tool_max_rect.z = new_point.z; }


                    tool_grid.push_back(new_point);

                }

            }
        }
    }
  

    tool_min_rect.x -= 1;
    tool_min_rect.y -= 1;

    tool_max_rect.x += 1;
    tool_max_rect.y += 1;


    X_tool_size = tool_max_rect.x - tool_min_rect.x ;
    Y_tool_size = tool_max_rect.y - tool_min_rect.y ;

    tool_dexel_grid.resize(X_tool_size * Y_tool_size);


    for (int i = 0; i < X_tool_size * Y_tool_size; i++)
    {
        tool_dexel_grid[i] = glm::vec2(100000000, 0);
    }

    for (int i = 0; i < tool_grid.size(); i++)
    {
        int curr_x = tool_grid[i].x;
        int curr_y = tool_grid[i].y;
        int curr_z = tool_grid[i].z - tool_min_rect.z;

        int num_curr_dexel = (curr_x - tool_min_rect.x) + X_tool_size * (curr_y - tool_min_rect.y);

        int dexel_min = tool_dexel_grid[num_curr_dexel].x;

        if (tool_dexel_grid[num_curr_dexel].x == 100000000 && tool_dexel_grid[num_curr_dexel].y == 0)
        {
            tool_dexel_grid[num_curr_dexel].x = curr_z;
            tool_dexel_grid[num_curr_dexel].y = 1;
        }

        else
        {
            int dexel_max = tool_dexel_grid[num_curr_dexel].x + tool_dexel_grid[num_curr_dexel].y;

            if (curr_z < dexel_min)
            {
                tool_dexel_grid[num_curr_dexel].x = curr_z;
                tool_dexel_grid[num_curr_dexel].y += (dexel_min - curr_z);
            }

            if (curr_z > dexel_max)
            {
                tool_dexel_grid[num_curr_dexel].y += curr_z - dexel_max;
            }
        }

       

    }
 
}



void Grid3D::grid_dexel_draw_dyn()
{
    grid_draw.clear();
    
    for (int j = 0; j < X_blank_size * Y_blank_size; j++)
    {
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

    }
    
    for (int i = 0; i < tool_grid.size(); i++)
    {
        //grid_draw.push_back(glm::vec4(tool_grid[i], 1));
    }

    for (int i = 0; i < tool_dexel_grid.size(); i++)
    {

        if (tool_dexel_grid[i].y != 0)
        {
            grid_draw.push_back(glm::vec4(i % X_tool_size - X_tool_size  + tool_min_rect.x + X_tool_size, (i / X_tool_size) % Y_tool_size - Y_tool_size  + tool_min_rect.y + Y_tool_size, tool_dexel_grid[i].x + tool_min_rect.z, tool_dexel_grid[i].y));
        }

    }

}



bool Grid3D::Scalar_cyl(float r, float x, float y)
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





glm::vec4 Grid3D::get_vert_by_num(int i)
{
    return glm::vec4(i % X, (i / X) % Y, i / (X * Y), 1);
}


int Grid3D::get_num_by_vert(glm::vec4 vertex)
{
    return vertex.x + vertex.y * X + vertex.z * X * Y;
}

