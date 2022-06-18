#pragma once
#include "Settings.h"

void translation_kb(int key, int action)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        vert = 1;
    else if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
        vert = 0;

    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        vert = -1;
    else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
        vert = 0;

    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        horiz = 1;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
        horiz = 0;

    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        horiz = -1;
    else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
        horiz = 0;
}
void rotation_kb(int key, int action)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        angle_change = 1;
    else if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
        angle_change = 0;

    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        angle_change = -1;
    else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
        angle_change = 0;
}
void scaling_kb(int key, int action)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        scale_y = 1;
    else if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
    {
        sx = 1;
        sy = 1;
        scale_y = 0;
    }

    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        scale_y = -1;
    else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
    {
        sx = 1;
        sy = 1;
        scale_y = 0;
    }

    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        scale_x = 1;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
    {
        sx = 1;
        sy = 1;
        scale_x = 0;
    }

    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        scale_x = -1;
    else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
    {
        sx = 1;
        sy = 1;
        scale_x = 0;
    }
}
