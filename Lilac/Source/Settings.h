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
        {0.407, 0.478, 0}, {0.874, 0.847, 0.003}, {1, 0.976, 0.239}, {0.996, 0.984, 0.623}, {1, 0.992, 0.760},
        {0.337, 0.250, 0.121}, {0.619, 0.454, 0.2}, {0.960, 0.580, 0}, {1, 0.772, 0.419}, {1, 0.898, 0.741},
        {0.407, 0.203, 0.050}, {0.737, 0.407, 0.160}, {0.850, 0.560, 0.349}, {0.933, 0.709, 0.545}, {0.972, 0.831, 0.729},
        {0.505, 0.156, 0.074}, {0.658, 0.172, 0.062}, {0.941, 0.192, 0.019}, {0.949, 0.396, 0.270}, {0.988, 0.568, 0.474},
        {0.407, 0.050, 0.066 }, {0.654, 0.066, 0.086}, {0.901, 0.078, 0.105}, {0.956, 0.443, 0.458}, {0.984, 0.698, 0.705},
        {0.584, 0.058, 0.290 }, {0.733, 0.105, 0.384}, {0.850, 0.247, 0.513}, {0.921, 0.458, 0.662}, {0.980, 0.741, 0.847},
        {0.741, 0, 0.415}, {0.992, 0.031, 0.568}, {0.996, 0.364, 0.717}, {0.992, 0.607, 0.823}, {1, 0.862, 0.937},
        {0.309, 0.031, 0.266}, {0.556, 0.043, 0.474}, {0.843, 0.058, 0.717}, {0.968, 0.349, 0.870}, {0.996, 0.764, 0.956},
        {0.258, 0.133, 0.266}, {0.466, 0.235, 0.486}, {0.662, 0.352, 0.686}, {0.784, 0.580, 0.8}, {0.886, 0.784, 0.894},
        {0.305, 0.070, 0.490}, {0.482, 0.105, 0.772}, {0.647, 0.313, 0.905}, {0.756, 0.521, 0.937}, {0.909, 0.823, 0.976},
        {0.180, 0.062, 0.415}, {0.301, 0.094, 0.705}, {0.407, 0.156, 0.901}, {0.658, 0.517, 0.945}, {0.835, 0.764, 0.976},
        {0.058, 0.023, 0.458}, {0.117, 0.070, 0.670}, {0.227, 0.168, 0.913}, {0.458, 0.415, 0.945}, {0.709, 0.686, 0.972},
        {0.027, 0.113, 0.411}, {0.050, 0.211, 0.749}, {0.196, 0.364, 0.945}, {0.486, 0.596, 0.972}, {0.772, 0.819, 0.988},
        {0.031, 0.278, 0.466}, {0.039, 0.439, 0.741}, {0.113, 0.6, 0.968}, {0.396, 0.729, 0.984}, {0.670, 0.850, 0.988},
        {0.031, 0.376, 0.447}, {0.054, 0.639, 0.768}, {0.196, 0.827, 0.960}, {0.458, 0.890, 0.980}, {0.772, 0.949, 0.988},
        {0.031, 0.427, 0.4}, {0.047, 0.690, 0.643}, {0.066, 0.933, 0.870}, {0.384, 0.956, 0.913}, {0.694, 0.984, 0.964},
        {0.027, 0.392, 0.231}, {0.043, 0.615, 0.364}, {0.074, 0.905, 0.541}, {0.4, 0.956, 0.713}, {0.737, 0.984, 0.874},
        {0.031, 0.447, 0.141}, {0.043, 0.756, 0.235}, {0.160, 0.960, 0.372}, {0.501, 0.976, 0.631}, {0.772, 0.988, 0.827},
        {0.552, 0.533, 0.027}, {0.819, 0.792, 0.039}, {0.964, 0.933, 0.156}, {1, 0.976, 0.439}, {0.996, 0.984, 0.643},
        {0, 0, 0}, {0.270, 0.290, 0.274}, {0.466, 0.494, 0.466}, {0.654, 0.666, 0.654}, {0.839, 0.843, 0.839}
};
std::vector<Button> modes;

std::pair<int, int> selected_tl = { 0,0 };
std::pair<int, int> selected_br = { 0,0 };
bool col_selected = false;
int col_idx;

std::pair<int, int> menu_selected_tl = { 0,0 };
std::pair<int, int> menu_selected_br = { 0,0 };

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