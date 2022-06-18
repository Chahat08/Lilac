#include "Shapes.h"
#include <iostream>

void printColorPresets()
{
    std::cout << "\t\tCOLOR PRESETS:" << std::endl;
    std::cout << "\t\t1. Blue" << std::endl;
    std::cout << "\t\t2. Green" << std::endl;
    std::cout << "\t\t3. Red" << std::endl;
    std::cout << "\t\t4. Black" << std::endl;
    std::cout << "\t\t5. Yellow" << std::endl;
    std::cout << "\t\t6. Pink" << std::endl;
    std::cout << "\t\t7. Orange" << std::endl;
    std::cout << "\t\t8. Sky Blue" << std::endl;
    std::cout << "\t\t9. Purple" << std::endl;
    std::cout << "\t\t: ";
}

void ShapeProperties::display_props(int t)
{
    //std::cout << "\tEP 1: " << Line::P1.first << " " << default_color[1] << " " << default_color[2] << std::endl;
    std::cout << "\t\tColor (RGB): " << default_color[0] << " " << default_color[1] << " " << default_color[2] << std::endl;
    std::cout << "\t\tThickness: " << default_thickness << std::endl;
    std::cout << "\t\tStyle: " << default_style << std::endl;
    if (t == 0)
    {
        std::cout << "\t\tEndpoints Color (RGB): " << default_ep_color[0] << " " << default_ep_color[1] << " " << default_ep_color[2] << std::endl;
        std::cout << "\t\tEndpoints Size (px): " << default_ep_size << std::endl;
    }
    else
    {
        std::cout << "\t\tCenter Color (RGB): " << default_ep_color[0] << " " << default_ep_color[1] << " " << default_ep_color[2] << std::endl;
        std::cout << "\t\tCenter Size (px): " << default_ep_size << std::endl;
    }
}
void ShapeProperties::changeColor(GLdouble r, GLdouble g, GLdouble b)
{
    default_color[0] = r;
    default_color[1] = g;
    default_color[2] = b;
}
void ShapeProperties::changeColorPresets()
{
    int choice;

    printColorPresets();

    std::cin >> choice;

    if (choice == 1) changeColor(0.0, 0.0, 1.0);
    else if (choice == 2) changeColor(0.0, 1.0, 0.0);
    else if (choice == 3) changeColor(1.0, 0.0, 0.0);
    else if (choice == 4) changeColor(0.0, 0.0, 0.0);
    else if (choice == 5) changeColor(1.0, 1.0, 0.0);
    else if (choice == 6) changeColor(1.0, 0.0, 0.5);
    else if (choice == 7) changeColor(1.0, 0.5, 0.0);
    else if (choice == 8) changeColor(0.0, 0.75, 1.0);
    else if (choice == 9) changeColor(0.5, 0.0, 1.0);
}
void ShapeProperties::changeThickness(int t)
{
    default_thickness = t;
}
void ShapeProperties::changeStyle(std::string s)
{
    default_style = s;
}
void ShapeProperties::changeStylePresets()
{
    int choice;

    std::cout << "\t\tSTYLE PRESETS:" << std::endl;
    std::cout << "\t\t0. ....................(Plot 1, Skip 0)" << std::endl;
    std::cout << "\t\t1. . . . . . . . . . . (Plot 1, Skip 1)" << std::endl;
    std::cout << "\t\t2. .. .. .. .. .. .. ..(Plot 2, Skip 1)" << std::endl;
    std::cout << "\t\t3. ... ... ... ... ... (Plot 3, Skip 1)" << std::endl;
    std::cout << "\t\t4. .. . .. . .. . .. . (Plot 2, Skip 1, Plot 1, Skip 1)" << std::endl;
    std::cout << "\t\t5. ..   ..   ..   ..   (Plot 2, Skip 3)" << std::endl;
    std::cout << "\t\t6. .... .... .... .... (Plot 4, Skip 1)" << std::endl;
    std::cout << "\t\t7. ....  ....  ....  ..(Plot 4, Skip 2)" << std::endl;
    std::cout << "\t\t8. ... .. ... .. ... ..(Plot 3, Skip 1, Plot 2, Skip 1)" << std::endl;
    std::cout << "\t\t9. ....    ....    ....(Plot 4, Skip 4)" << std::endl;
    std::cout << "\t\t: ";

    std::cin >> choice;

    if (choice == 1) changeStyle("10");
    else if (choice == 2) changeStyle("110");
    else if (choice == 3) changeStyle("1110");
    else if (choice == 4) changeStyle("11010");
    else if (choice == 5) changeStyle("11000");
    else if (choice == 6) changeStyle("11110");
    else if (choice == 7) changeStyle("111100");
    else if (choice == 8) changeStyle("1110110");
    else if (choice == 9) changeStyle("11110000");
}
void ShapeProperties::changeColorEP(GLdouble r, GLdouble g, GLdouble b)
{
    default_ep_color[0] = r;
    default_ep_color[1] = g;
    default_ep_color[2] = b;
}
void ShapeProperties::changeColorEPPresets()
{
    int choice;

    printColorPresets();

    std::cin >> choice;

    if (choice == 1) changeColorEP(0.0, 0.0, 1.0);
    else if (choice == 2) changeColorEP(0.0, 1.0, 0.0);
    else if (choice == 3) changeColorEP(1.0, 0.0, 0.0);
    else if (choice == 4) changeColorEP(0.0, 0.0, 0.0);
    else if (choice == 5) changeColorEP(1.0, 1.0, 0.0);
    else if (choice == 6) changeColorEP(1.0, 0.0, 0.5);
    else if (choice == 7) changeColorEP(1.0, 0.5, 0.0);
    else if (choice == 8) changeColorEP(0.0, 0.75, 1.0);
    else if (choice == 9) changeColorEP(0.5, 0.0, 1.0);
}
void ShapeProperties::changeSizeEP(int s)
{
    default_ep_size = s;
}
int ShapeProperties::getThickness()
{
    return default_thickness;
}