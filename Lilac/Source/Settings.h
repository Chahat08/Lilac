#pragma once
#include "Shapes.h"
#include "WindowProperties.h"
#include "Button.h"
#include <map>

DefaultLine def_line;
Window w;

std::vector<Shape> shapes;
std::vector<BezierCurve> beziers;
std::vector<BSplineCurve> splines;

std::vector<int> deleted;
int shape_number = -1;
int draw_mode = 0; // 0 = draw lines, 1 = draw circles, 2 = bezier curves, 3 = spline curves
bool bc_selection_mode = false; // selection mode for bezier curves
bool sc_selection_mode = false; // selection mode for spline curves
int sc_k_val = 1; // chosen degree for spline curves

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

int sc = 0;

std::map<std::pair<int, int>, ColorRGB> board;

double mouse_x, mouse_y;
int FILL_MODE = 0; // 0 = draw mode, 1 = flood fill, 2 = boundary fill, 3 = scanline fill

ColorRGB boundary_color;

/* TRANSFORMATIONS */
int transformation = 0; // 1: translation, 2: rotation, 3: scaling

// Translation
int vert = 0, horiz = 0;

// Rotation
std::pair<int, int> pivot;
std::pair<int, int> orig1;
std::pair<int, int> orig2;
bool original_set = false;
bool pivot_set = false;
float angle = 0;
int angle_change = 0; // 1: scrolling up, -1: scrolling down

// Scaling
float sx = 1;
float sy = 1;
int scale_x = 0;
int scale_y = 0;