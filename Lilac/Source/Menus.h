#pragma once
#include <string>
#include <iostream>
#include "Settings.h"

namespace MENUS
{
    std::string getStyle(int s)
    {
        std::string bin;
        while (s)
        {
            bin += std::to_string(s % 2);
            s /= 2;
        }
        std::reverse(bin.begin(), bin.end());
        return bin;
    }
    void edit_style()
    {
        int choice2;

        std::cout << "\nEDITING LINE STYLE" << std::endl;
        std::cout << "\t1. Choose from presets" << std::endl;
        std::cout << "\t2. Define hex value" << std::endl;
        std::cout << "\t: ";



        std::cin >> choice2;
        if (choice2 == 1)
            shapes[shape_number].changeStylePresets();
        else
        {
            int s;
            std::cout << "\n\tEnter the hex value: ";
            std::cin >> std::hex >> s >> std::dec;
            std::string str = getStyle(s);
            shapes[shape_number].changeStyle(str);
            std::cout << "\tStyle changed to: " << str << std::endl;
        }
    }
    void show_kb_options()
    {
        std::cout << "L: Draw Lines" << std::endl;
        std::cout << "C: Draw Circles" << std::endl;
        std::cout << "1: Flood Fill Color" << std::endl;
        std::cout << "2: Boundary Fill Color" << std::endl;
        std::cout << "3: Scan-Line Fill Color" << std::endl;
        std::cout << "F: Color filling mode (scan-line fill)" << std::endl;
        std::cout << "Scroll: Change Thickness" << std::endl;
        std::cout << "S: Change Style, console input" << std::endl;
        std::cout << "D: Delete recent-most shape" << std::endl;
        std::cout << "O: Show Keyboard Options" << std::endl;
    }
}

