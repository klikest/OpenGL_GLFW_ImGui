#include "Grid3D.h"



void Grid3D::create_blank_dexel(float r, float h)
{
    X_blank_size = 2 * r;
    Y_blank_size = 2 * r;
    fill_grid(X_blank_size, Y_blank_size, 1);

    for (int i = 0; i < dexel_blank[0].size(); i++)
    {
        if (Scalar_cyl(r, i % X_blank_size - X_blank_size/2, (i / X_blank_size) % Y_blank_size - Y_blank_size/2))
        {
            dexel_blank[0][i].y = h;
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
}

void Grid3D::fill_grid(int x_size, int y_size, int z_size)
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

