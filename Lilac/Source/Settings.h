#pragma once
#include "Button.h"

std::vector<Button> colors;
std::vector<ColorRGB> col_vals = {
        {1,0,0},{0, 1, 0},{0,0,1} ,
        {0.976, 0.031, 0.992},{0.984, 0.882, 0.196 }, { 0.984, 0.556, 0.196 },
        {0.627, 0.196, 0.984}, {0.196, 0.6, 0.984}, {0.5, 0, 0.5},
        {0, 0.5, 0.5},{0.592, 0.250, 0.066}, {0.5, 0.5, 0}, {0.549, 0.549, 0.549},
        {0,0,0}
};

std::pair<int, int> selected_tl = { 0,0 };
std::pair<int, int> selected_br = { 0,0 };
bool col_selected = false;
int col_idx;