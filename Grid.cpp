#include "Grid.h"

void Grid::create_draw_grid()
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

bool Grid::scalar_cyl(float r, float x, float y)
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

bool Grid::scalar_cyl_tool(float r, float x, float y)
{
    if ((x * x) + (y * y) <= (r * r) && (x * x) + (y * y) >= (r * r) - 0.1 * (r * r))
    {
        return true;
    }
    else
    {
        return false;
    }
}



bool Grid::scalar_sphere(float r, float x, float y, float z)
{
    if ((x * x) + (y * y) + (z * z) > (r * r) - 0.2 * (r * r) && (x * x) + (y * y) + (z * z) < (r * r))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Grid::create_cyl(int r, int h)
{
    grid_blank.clear();
    for (int i = 0; i < h; i++)
    {
        for (int j = -r; j < r; j++)
        {
            for (int k = -r; k < r; k++)
            {
                if (scalar_cyl(r, j, k))
                {
                    grid_blank.push_back(glm::vec3(i, j, -k));
                }


            }
        }
    }

}

void Grid::create_tool(int r, int h, float dx, float dy, float dz, float x_a, float y_a, float z_a)
{
    grid_tool.clear();
    for (int i = 0; i < h; i += 1)
    {
        for (int j = -r; j < r; j += 1)
        {
            for (int k = -r; k < r; k += 1)
            {
                if (scalar_cyl_tool(r, j, k) || (i == 0 && scalar_cyl(r, j, k)) || (i == 1 && scalar_cyl(r, j, k)) || (i == 2 && scalar_cyl(r, j, k)) || (i == h - 1 && scalar_cyl(r, j, k)) || (i == h - 2 && scalar_cyl(r, j, k)) || (i == h - 3 && scalar_cyl(r, j, k)))
                {
                    glm::mat4 trans_y = glm::mat4(1.0f);
                    trans_y = glm::rotate(trans_y, glm::radians(x_a), glm::vec3(0.0, 1.0, 0.0));
                    glm::vec4 coords__ = trans_y * glm::vec4(i, j, k, 1.0f);

                    glm::mat4 trans_x = glm::mat4(1.0f);
                    trans_x = glm::rotate(trans_x, glm::radians(y_a), glm::vec3(1.0, 0.0, 0.0));
                    glm::vec4 coords_ = trans_x * coords__;

                    glm::mat4 trans_z = glm::mat4(1.0f);
                    trans_z = glm::rotate(trans_z, glm::radians(z_a), glm::vec3(1.0, 0.0, 1.0));
                    glm::vec4 coords = trans_z * coords_;

                    grid_tool.push_back(glm::vec3(round(dx + coords.x), round(dy + coords.y), round(dz + coords.z)));

                }

            }
        }
    }

}


void Grid::create_sphere(int r, float dx, float dy, float dz)
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
                    grid_tool.push_back(glm::vec3(i * 2 + dx, j * 2 + dy, -k * 2 + dz));
                }
                else
                {

                }

            }

        }
    }

}

void Grid::bolean_cut()
{
    float t_x_min = grid_tool[0].x, t_x_max = grid_tool[0].x, t_y_min = grid_tool[0].y, t_y_max = grid_tool[0].y, t_z_min = grid_tool[0].z, t_z_max = grid_tool[0].z;
    float b_x_min = grid_blank[0].x, b_x_max = grid_blank[0].x, b_y_min = grid_blank[0].y, b_y_max = grid_blank[0].y, b_z_min = grid_blank[0].z, b_z_max = grid_blank[0].z;

    for (int i = 0; i < grid_tool.size(); i++)
    {
        float new_x = grid_tool[i].x;
        float new_y = grid_tool[i].y;
        float new_z = grid_tool[i].z;
        if (new_x > t_x_max) { t_x_max = new_x; }
        if (new_x < t_x_min) { t_x_min = new_x; }
        if (new_y > t_y_max) { t_y_max = new_y; }
        if (new_y < t_y_min) { t_y_min = new_y; }
        if (new_z > t_z_max) { t_z_max = new_z; }
        if (new_z < t_z_min) { t_z_min = new_z; }
    }
    for (int i = 0; i < grid_blank.size(); i++)
    {
        float new_x = grid_blank[i].x;
        float new_y = grid_blank[i].y;
        float new_z = grid_blank[i].z;
        if (new_x > b_x_max) { b_x_max = new_x; }
        if (new_x < b_x_min) { b_x_min = new_x; }
        if (new_y > b_y_max) { b_y_max = new_y; }
        if (new_y < b_y_min) { b_y_min = new_y; }
        if (new_z > b_z_max) { b_z_max = new_z; }
        if (new_z < b_z_min) { b_z_min = new_z; }
    }


    grid_draw.clear();

    tmp_vec.clear();

    for (int i = 0; i < grid_blank.size(); i++)
    {
        bool is_void = true;
        if (!(grid_blank[i].x > t_x_max || grid_blank[i].x < t_x_min || grid_blank[i].y > t_y_max || grid_blank[i].y < t_y_min || grid_blank[i].z > t_z_max || grid_blank[i].z < t_z_min))
        {
            for (int j = 0; j < grid_tool.size(); j++)
            {
                if (!(grid_tool[j].x > b_x_max || grid_tool[j].x < b_x_min || grid_tool[j].y > b_y_max || grid_tool[j].y < b_y_min || grid_tool[j].z > b_z_max || grid_tool[j].z < b_z_min))
                {

                    if ((is_void == false) || grid_tool[j] == grid_blank[i])
                    {
                        //grid_blank.erase(std::remove(grid_blank.begin(), grid_blank.end(), grid_blank[i]), grid_blank.end());
                        is_void = false;
                    }
                }
            }

        }
        if (is_void)
        {
            tmp_vec.push_back(grid_blank[i]);
        }

    }

    grid_blank.clear();
    grid_blank = tmp_vec;
    
    for (int i = 0; i < grid_blank.size(); i++)
    {
        grid_draw.push_back(grid_blank[i]);
    }

    for (int j = 0; j < grid_tool.size(); j++)
    {
        grid_draw.push_back(grid_tool[j]);
    }

}
