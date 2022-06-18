#pragma once
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShapeProperties
{
protected:
    std::vector<GLdouble> default_color = { 0.0, 0.0, 1.0 }; // r = 0.0, g = 0.0, b = 1.0;

    int default_thickness = 1; // default 1 px

    std::string default_style = "1"; // plot all

    std::vector<GLdouble> default_ep_color = { 1.0, 0.0, 0.0 }; // endpoints color
    int default_ep_size = 4; //endpoints size

public:
    void display_props(int);

    // set methods
    void changeColor(GLdouble, GLdouble, GLdouble);
    void changeColorPresets();
    void changeThickness(int);
    void changeStyle(std::string);
    void changeStylePresets();
    void changeColorEP(GLdouble, GLdouble, GLdouble);
    void changeColorEPPresets();
    void changeSizeEP(int);

    // get methods
    int getThickness();
};