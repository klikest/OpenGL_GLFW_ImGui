#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "UI_Data.h"
#include "Grid.h"
 

float UI_Data::get_delTime()
{
	return delta_time;
}

void UI_Data::get_inputs(GLFWwindow* window, Grid grid)
{
    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS) { x_t += 1; }
    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS) { x_t -= 1; }
    if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS) { z_t -= 1; }
    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS) { z_t += 1; }
    if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS) { y_t += 1; }
    if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS) { y_t -= 1; }
    if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS) { r_t += 1; }
    if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS) { r_t -= 1; }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){r_b -= 1; grid.create_cyl(r_b, h_b);}
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){r_b += 1; grid.create_cyl(r_b, h_b);}
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){h_b -= 1; grid.create_cyl(r_b, h_b);}
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS){h_b += 1; grid.create_cyl(r_b, h_b);}
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS){alfa += 0.01;}
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS){alfa -= 0.01;}
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS){h_t += 1;}
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS){h_t -= 1;}
}


