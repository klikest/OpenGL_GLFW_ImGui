#include "Grid3D.h"
#include "thread"
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>


void Grid3D::create_blank_dexel(float r, float h)
{
    X_blank_size = 2 * r;
    Y_blank_size = 2 * r;
    fill_grid_blank(X_blank_size, Y_blank_size, 1);

    for (int i = 0; i < dexel_blank[0].size(); i++)
    {
        if (Scalar_cyl(r, i % X_blank_size - X_blank_size/2, (i / X_blank_size) % Y_blank_size - Y_blank_size/2))
        {
            dexel_blank[0][i].y = h;
        }
    }

}





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

void Grid3D::create_tool_dexel_dyn(float r, float h, float dx, float dy, float dz, float ax, float ay, float az)
{
    tool_dexel_cloud.clear();
    tool_grid.clear();

    int x_max = -10000, y_max = -10000, z_max = -10000;
    int x_min = 10000, y_min = 10000, z_min = 10000;

    for (int i = -r; i <= r; i += 1)
    {
        for (int j = -r; j <= r; j += 1)
        {
            for (int k = 0; k < h; k += 1)
            {
                if (Scalar_cyl(r, i, j))
                {

                    glm::vec4 coords = glm::vec4(i+r, j+r, k, 1.0f);

                    int x_new = round(coords.x );
                    int y_new = round(coords.y );
                    int z_new = round(coords.z);

                    if (x_new > x_max) { x_max = x_new; }
                    if (x_new < x_min) { x_min = x_new; }
                    if (y_new > y_max) { y_max = y_new; }
                    if (y_new < y_min) { y_min = y_new; }
                    if (z_new > z_max) { z_max = z_new; }
                    if (z_new < z_min) { z_min = z_new; }

                    tool_grid.push_back(glm::vec3(x_new , y_new , z_new ));

                }

            }
        }
    }
    
    X_tool_size = x_max - x_min;
    Y_tool_size = y_max - y_min;

    tool_dexel_grid.resize(X_tool_size * Y_tool_size);
    for (int i = 0; i < tool_dexel_grid.size(); i++)
    {
        tool_dexel_grid[i] = glm::vec2(100000000, 0);
    }


    for (int i = 0; i < tool_grid.size(); i++)
    {
        int curr_x = tool_grid[i].x;
        int curr_y = tool_grid[i].y;
        int curr_z = tool_grid[i].z;

        int curr_z_min = tool_dexel_grid[curr_x + curr_y * X_tool_size].x;

        tool_dexel_grid[curr_x + curr_y * X_tool_size].y += 1; // Каждое попадание в нужную точку сетки увеличивает длину декселя на 1

        if (curr_z < curr_z_min)
        {
            tool_dexel_grid[curr_x + curr_y * X_tool_size].x = curr_z; // Если текущее значение точки меньше начальной точки декселя -> обновить начальную точку декселя
        }


    }



}




void Grid3D::create_tool_dexel(float r, float h, float dx, float dy, float dz, float ax, float ay, float az)
{
    dexel_tool.clear();

    int x_max=dx, y_max=dy, z_max=dz;
    int x_min=dx, y_min=dy, z_min=dz;

    tool_grid.clear();

    for (int i = 0; i < h; i += 1)
    {
        for (int j = -r; j < r; j += 1)
        {
            for (int k = -r; k < r; k += 1)
            {
                if (Scalar_cyl(r, j, k))
                {
                    glm::mat4 trans_y = glm::mat4(1.0f);
                    trans_y = glm::rotate(trans_y, glm::radians(ax), glm::vec3(1.0f, 0.0f, 0.0f));
                    glm::vec4 coords__ = trans_y * glm::vec4(i, j, k, 1.0f);

                    glm::mat4 trans_x = glm::mat4(1.0f);
                    trans_x = glm::rotate(trans_x, glm::radians(ay), glm::vec3(0.0f, 1.0f, 0.0f));
                    glm::vec4 coords_ = trans_x * coords__;

                    glm::mat4 trans_z = glm::mat4(1.0f);
                    trans_z = glm::rotate(trans_z, glm::radians(az), glm::vec3(0.0f, 0.0f, 1.0f));
                    glm::vec4 coords = trans_z * coords_;

                    int x_new = round(dx + coords.x);
                    int y_new = round(dy + coords.y);
                    int z_new = round(dz + coords.z);

                    if (x_new > x_max) { x_max = x_new; }
                    if (x_new < x_min) { x_min = x_new; }
                    if (y_new > y_max) { y_max = y_new; }
                    if (y_new < y_min) { y_min = y_new; }
                    if (z_new > z_max) { z_max = z_new; }
                    if (z_new < z_min) { z_min = z_new; }

                    tool_grid.push_back(glm::vec3(x_new, y_new, z_new));

                }

            }
        }
    }
    X_tool_size = x_max - x_min + 1;
    Y_tool_size = y_max - y_min + 1;

    fill_grid_tool(X_tool_size, Y_tool_size);

    for (int i = 0; i < tool_grid.size(); i++)
    {
        int x = tool_grid[i].x;
        int y = tool_grid[i].y;
        int z = tool_grid[i].z;

        int curr_z = dexel_tool[x + y * (X_tool_size) + z * (X_tool_size) * (Y_tool_size)].x;
        int curr_len = dexel_tool[x + y * (X_tool_size)+z * (X_tool_size) * (Y_tool_size)].y;

        int new_z = z;
        int new_len = 0;

        if (new_z < curr_z)
        {
            dexel_tool[x + y * (X_tool_size) + z * (X_tool_size) * (Y_tool_size)] = glm::vec2(new_z, curr_len+1);
        }
        else
        {
            dexel_tool[x + y * (X_tool_size) + z * (X_tool_size) * (Y_tool_size)] = glm::vec2(curr_z, curr_len + 1);
        }

        
    }

}



void Grid3D::grid_dexel_draw()
{
    grid_draw.clear();

    for (int i = 0; i < dexel_blank.size(); i++)
    {
        for (int j = 0; j < dexel_blank[i].size(); j++)
        {
            if (dexel_blank[i][j].y != 0)
            {
                grid_draw.push_back(glm::vec4(j % X_blank_size - X_blank_size / 2, (j / X_blank_size) % Y_blank_size - Y_blank_size / 2, dexel_blank[i][j].x, dexel_blank[i][j].y));
            }
        }
    }

    for (int i = 0; i < tool_dexel_grid.size(); i++)
    {

        if (tool_dexel_grid[i].y != 0)
        {
            grid_draw.push_back(glm::vec4(i % X_blank_size - X_blank_size / 2, (i / X_blank_size) % Y_blank_size - Y_blank_size / 2, tool_dexel_grid[i].x, tool_dexel_grid[i].y));
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

    for (int i = 0; i < tool_dexel_grid.size(); i++)
    {

        if (tool_dexel_grid[i].y != 0)
        {
            grid_draw.push_back(glm::vec4(i % X_tool_size - X_tool_size / 2, (i / X_tool_size) % Y_tool_size - Y_tool_size / 2, tool_dexel_grid[i].x, tool_dexel_grid[i].y));
        }

    }

}




void Grid3D::fill_grid_blank(int x_size, int y_size, int z_size)
{
    dexel_blank.clear();

    for (int i = 0; i < z_size; i++)
    {   
        std::vector<glm::vec2> slice;
        for (int j = 0; j < (x_size * y_size); j++)
        {
            slice.push_back(glm::vec2(0, 0));
        }
        dexel_blank.push_back(slice);
    }

}

void Grid3D::fill_grid_tool(int x_size, int y_size)
{
    dexel_tool.clear();
    for (int i = 0; i < (x_size * y_size); i++)
    {
        dexel_tool.push_back(glm::vec2(10000, 0));
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


void Grid3D::create_blank_grid(float r, float h)
{
    grid.clear();

    X = 2 * r +2;
    Y = 2 * r +2;
    Z = h ;

    for (int i = 0; i < h; i++)
    {
        for (int j = -r-1; j < r+1; j++)
        {
            for (int k = -r-1; k < r+1; k++)
            {
                if (Scalar_cyl(r, j, k))
                {
                    grid.push_back(glm::vec4(k, j, i, 1.0f));
                }
                else
                {
                    grid.push_back(glm::vec4(k, j, i, 0.0f));
                }
            }
        }
    }
}



void Grid3D::set_draw()
{
    grid_test.clear();

    for (int i = 0; i < grid.size(); i++)
    {
        if (grid[i].w == 1)
        {
            if ((grid[i+1].w == 0 || grid[i - 1].w == 0))
            {
                grid_test.push_back(grid[i]);
            }

            if ((i > X && i < grid.size() - X) && (grid[i + X].w == 0 || grid[i - X].w == 0))
            {
                grid_test.push_back(grid[i]);
            }

            if ( (i > (X*Y) && i < (grid.size() -(X*Y))   ) )
            {
                if ((grid[i + X * Y].w == 0 || grid[i - X * Y].w == 0))
                {
                    grid_test.push_back(grid[i]);
                }

            }
            else
            {
                grid_test.push_back(grid[i]);
            }

        }
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

