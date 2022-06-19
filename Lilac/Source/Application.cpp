#include "WindowProperties.h"
#include "Shapes.h"
#include "Button.h"
#include "Settings.h"
#include "menus.h"
#include "transformations.h"
#include <algorithm>
#include <queue>
//#include "CImg.h"

//#define WIDTH 500
//#define HEIGHT 540

#define WIDTH 1200
#define HEIGHT 800

ColorRGB pointColor(GLint x, GLint y) {
	ColorRGB color;
	glReadPixels(x + 600, HEIGHT + y - 400, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}
//bool hibyeblah = true;
void putPoint(GLint x, GLint y, ColorRGB color, int sz = 1) {
	glPointSize(sz);
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glPointSize(1);
	glFlush();
}

void drawBezierCurve(BezierCurve& b, int is_spline = false)
{
	if (b.equation.size() == 0) return;

	if (!b.cont_pt_chosen && !is_spline)
		for (auto& poly : b.equation)
			putPoint(poly.point.first, poly.point.second, col_vals[0], 5);

	ColorRGB col(b.color[0], b.color[1], b.color[2]);
	float x = 0, y = 0;

	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glColor3f(b.color[0], b.color[1], b.color[2]);
	glVertex2i(b.equation.front().point.first, b.equation.front().point.second);
	for (float t = 0; t <= 1; t += 0.05)
	{
		x = 0;
		y = 0;
		for (auto& poly : b.equation)
		{
			x += poly.bin_coeff * pow((1 - t), poly.one_minus_t_pow) * pow(t, poly.t_pow) * poly.point.first;
			y += poly.bin_coeff * pow((1 - t), poly.one_minus_t_pow) * pow(t, poly.t_pow) * poly.point.second;
		}
		glVertex2i(x, y);
	}
	glVertex2i(b.equation.back().point.first, b.equation.back().point.second);
	glEnd();
	glLineWidth(1);
}
void drawBSplineCurve(BSplineCurve& b)
{
	if (!b.cont_pt_chosen)
		for (auto& p : b.cp)
			putPoint(p.first, p.second, col_vals[0], 5);

	for (auto& bez : b.bcs)
		drawBezierCurve(bez, true);

}

void rotate_shape()
{
	if (!original_set)
	{
		if (shapes[shape_number].type == 0)
		{
			orig1 = shapes[shape_number].Line::getPoint1();
			orig2 = shapes[shape_number].Line::getPoint2();
		}
		else
		{
			orig1 = shapes[shape_number].Line::getPoint1();
		}
		original_set = true;
	}
	if (pivot_set)
	{
		putPoint(pivot.first, pivot.second, col_vals[0], 4);
		if (angle_change == 1)
		{
			angle += 0.01;
			shapes[shape_number].Rotate(pivot.first, pivot.second, angle, orig1, orig2);
		}
		else if (angle_change == -1)
		{
			angle -= 0.01;
			shapes[shape_number].Rotate(pivot.first, pivot.second, angle, orig1, orig2);
		}
	}
}
void scale_shape()
{
	std::cout << sx << " " << sy;
	if (scale_x)
	{
		if (scale_x == 1)
		{
			sx += 0.005;
			//if (sx == 0) sx = 0.005;
		}
		else
		{
			sx -= 0.005;
			//if (sx == 0) sx = -0.005;
		}
	}
	if (scale_y)
	{
		if (scale_y == 1)
		{
			sy += 0.005;
			//if (sy == 0) sy = 0.005;
		}
		else
		{
			sy -= 0.005;
			//if (sy == 0) sy = -0.005;
		}
	}

	shapes[shape_number].Scale(sx, sy);
}
void floodFill(int x, int y, ColorRGB prevColor, ColorRGB fillColor)
{
	std::queue<std::pair<int, int>> q;

	q.push({ x,y });

	while (!q.empty())
	{
		int x = q.front().first, y = q.front().second;
		if (pointColor(x, y) == prevColor)
		{
			putPoint(x, y, fillColor);
			board[{x, y}] = fillColor;

			q.push({ x + 1, y });
			q.push({ x - 1, y });
			q.push({ x, y + 1 });
			q.push({ x, y - 1 });
		}
		q.pop();
	}
}
void drawOctants(Shape& c, int x, int y)
{
	int cent_x = c.Circle::P1.first, cent_y = c.Circle::P1.second;
	glBegin(GL_POINTS);
	glColor3d(c.default_color[0], c.default_color[1], c.default_color[2]);
	glVertex2i(cent_x + x, cent_y + y);
	glVertex2i(cent_x - x, cent_y + y);
	glVertex2i(cent_x + x, cent_y - y);
	glVertex2i(cent_x - x, cent_y - y);
	glVertex2i(cent_x + y, cent_y + x);
	glVertex2i(cent_x - y, cent_y + x);
	glVertex2i(cent_x + y, cent_y - x);
	glVertex2i(cent_x - y, cent_y - x);
	glEnd();
}
void bresenham_circle(Shape& c)
{
	glPointSize(1);

	int x = 0, y = c.radius;
	int d = 3 - 2 * c.radius;
	drawOctants(c, x, y);

	int i = 0;
	while (y >= x)
	{
		x++;
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;

		if (i == c.default_style.length()) i = 0;
		if (c.default_style[i++] == '0') continue;
		drawOctants(c, x, y);
	}
	glFlush();
}
void draw_circle(Shape& c)
{
	if (c.default_thickness == 1) { bresenham_circle(c); return; }
	else
	{
		int i = c.default_thickness % 2 == 0 ? -c.default_thickness / 2 + 1 : -c.default_thickness / 2;

		for (; i <= c.default_thickness / 2; ++i)
		{
			Shape shape(c.Circle::P1.first, c.Circle::P1.second, c.radius + i, c.default_color[0], c.default_color[1], c.default_color[2], c.default_style);
			bresenham_circle(shape);
		}
	}
}
void bresenham_line(Shape& l)
{
	glPointSize(1);

	int X1 = l.Line::P1.first, Y1 = l.Line::P1.second, X2 = l.P2.first, Y2 = l.P2.second;

	int dx = X2 - X1;
	int dy = Y2 - Y1;

	bool neg_slope = false;
	if (dy * dx < 0)
	{
		neg_slope = true;
		Y1 = -Y1;
		Y2 = -Y2;
		dy = -dy;
	}

	if (dx > dy && X1 > X2)
	{
		std::swap(X1, X2);
		std::swap(Y1, Y2);

		dx = -dx;
		dy = -dy;
	}
	else if (dy > dx && Y1 > Y2)
	{
		std::swap(X1, X2);
		std::swap(Y1, Y2);

		dx = -dx;
		dy = -dy;
	}

	int P;
	int i = 0;
	std::vector<std::pair<int, int>> pts;
	std::vector<short> plot;

	if (dx > dy)
	{
		P = 2 * dy - dx;

		for (int x = X1, y = Y1, p = P; x <= X2; ++i)
		{
			if (i > l.default_style.size() - 1) i = 0;
			if (l.default_style[i] == '1') plot.push_back(1);
			else plot.push_back(0);

			if (neg_slope) pts.push_back(std::make_pair(x, -y));
			else pts.push_back(std::make_pair(x, y));

			x += 1;

			if (p < 0)
			{
				p += 2 * dy;
			}
			else
			{
				p += 2 * dy - 2 * dx;
				y += 1;
			}
		}
	}
	else
	{
		P = 2 * dx - dy;

		for (int x = X1, y = Y1, p = P; y <= Y2; ++i)
		{
			if (i > l.default_style.size() - 1) i = 0;
			if (l.default_style[i] == '1') plot.push_back(1);
			else plot.push_back(0);

			if (neg_slope) pts.push_back(std::make_pair(x, -y));
			else pts.push_back(std::make_pair(x, y));

			y += 1;

			if (p < 0)
			{
				p += 2 * dx;
			}
			else
			{
				p += 2 * dx - 2 * dy;
				x += 1;
			}
		}
	}
	if (!plot.empty())
	{
		if (plot[plot.size() - 1] == 0)
		{
			for (int i = 0; i < plot.size() / 2; ++i)
				plot[plot.size() - i - 1] = plot[i];
		}
		for (int i = 0; i < pts.size(); ++i)
		{
			if (plot[i])
			{
				if (pts[i].first < -600 || pts[i].first > 600 || pts[i].second < -400 || pts[i].second>400) continue;
				glBegin(GL_POINTS);
				glColor3d(l.default_color[0], l.default_color[1], l.default_color[2]);
				glVertex2i(pts[i].first, pts[i].second);
				glEnd();
			}
		}
	}
	glFlush();
}
void draw_line(Shape& l)
{
	if (l.default_thickness == 1)
	{
		bresenham_line(l);
		return;
	}

	int i = l.default_thickness % 2 == 0 ? -l.default_thickness / 2 + 1 : -l.default_thickness / 2;

	float m = (l.P2.second - l.Line::P1.second) / (float)(l.P2.first - l.Line::P1.first);

	if (std::abs(m) <= 1)
	{
		for (; i <= l.default_thickness / 2; ++i)
		{
			Shape shape(l.Line::P1.first - i * m, l.Line::P1.second + i, l.P2.first - i * m, l.P2.second + i, l.default_color[0], l.default_color[1], l.default_color[2], l.default_style);
			bresenham_line(shape);
		}
	}
	else
	{
		for (; i <= l.default_thickness / 2; ++i)
		{
			Shape shape(l.Line::P1.first + i, l.Line::P1.second - i / m, l.P2.first + i, l.P2.second - i / m, l.default_color[0], l.default_color[1], l.default_color[2], l.default_style);
			bresenham_line(shape);
		}
	}
}
void showClicked()
{
	glBegin(GL_QUADS);
	glColor3d(0.976, 0.968, 0.862);
	glVertex2i(selected_tl.first, selected_tl.second);
	glVertex2i(selected_tl.first, selected_br.second);
	glVertex2i(selected_br.first, selected_br.second);
	glVertex2i(selected_br.first, selected_tl.second);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glColor3d(0, 0, 0);
	glVertex2i(menu_selected_tl.first, menu_selected_tl.second);
	glVertex2i(menu_selected_tl.first, menu_selected_br.second);
	glVertex2i(menu_selected_br.first, menu_selected_br.second);
	glVertex2i(menu_selected_br.first, menu_selected_tl.second);
	glEnd();
	glLineWidth(1);

}
void set_points(GLFWwindow* window, int pt)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	int x = xpos - 600;
	int y = 400 - ypos;

	// rotation set pivot
	if (transformation == 2)
	{
		pivot.first = x;
		pivot.second = y;
		pivot_set = true;
		return;
	}

	if (y <= colors[0].getTopLeft().second && y >= colors[colors.size()-1].getBtmRight().second && x>=colors[0].getTopLeft().first && x<=colors[colors.size()-1].getBtmRight().first)
	{
		int i = 0;
		for (auto& btn : colors)
		{
			if (x >= btn.getTopLeft().first && x <= btn.getBtmRight().first && y>=btn.getBtmRight().second && y<= btn.getTopLeft().second)
			{
				btn.clicked = !btn.clicked;
				if (btn.clicked)
				{
					colors[col_idx].clicked = false;
					col_idx = i;
					// std::cout << i << std::endl;
					selected_tl = { btn.getTopLeft().first + 5, btn.getTopLeft().second - 5 };
					selected_br = { btn.getBtmRight().first - 5, btn.getBtmRight().second + 5 };
					break;
				}
				else
				{
					col_idx = colors.size() - 1;
					selected_tl = { colors[colors.size() - 5].getTopLeft().first + 5,
									colors[colors.size() - 5].getTopLeft().second - 5 };
					selected_br = { colors[colors.size() - 5].getBtmRight().first - 5,
									colors[colors.size() - 5].getBtmRight().second + 5 };
					break;
				}
			}
			++i;
		}
		return;
	}


	if (y <= colors[0].getTopLeft().second && y >= colors[colors.size() - 1].getBtmRight().second && x >= colors[0].getTopLeft().first && x <= colors[colors.size() - 1].getBtmRight().first)
	{
		int i = 0;
		for (auto& btn : colors)
		{
			if (x >= btn.getTopLeft().first && x <= btn.getBtmRight().first && y >= btn.getBtmRight().second && y <= btn.getTopLeft().second)
			{
				btn.clicked = !btn.clicked;
				if (btn.clicked)
				{
					colors[col_idx].clicked = false;
					col_idx = i;
					// std::cout << i << std::endl;
					selected_tl = { btn.getTopLeft().first + 5, btn.getTopLeft().second - 5 };
					selected_br = { btn.getBtmRight().first - 5, btn.getBtmRight().second + 5 };
					break;
				}
				else
				{
					col_idx = colors.size() - 1;
					selected_tl = { colors[colors.size() - 5].getTopLeft().first + 5,
									colors[colors.size() - 5].getTopLeft().second - 5 };
					selected_br = { colors[colors.size() - 5].getBtmRight().first - 5,
									colors[colors.size() - 5].getBtmRight().second + 5 };
					break;
				}
			}
			++i;
		}
		return;
	}
	
	if (y <= 400 && y>=350 && x>=-390 && x<=310)
	{
		int i = 0;
		for (auto& btn : modes)
		{
			if (x >= btn.getTopLeft().first && x <= btn.getBtmRight().first && y >= btn.getBtmRight().second && y <= btn.getTopLeft().second)
			{
				btn.clicked = !btn.clicked;
				if (btn.clicked)
				{
					modes[draw_mode].clicked = false;
					draw_mode = i;
					// std::cout << i << std::endl;
					menu_selected_tl = { btn.getTopLeft().first + 5, btn.getTopLeft().second - 5 };
					menu_selected_br = { btn.getBtmRight().first - 5, btn.getBtmRight().second + 5 };
					break;
				}
				else
				{
					draw_mode = 0;
					menu_selected_tl = { colors[colors.size() - 5].getTopLeft().first + 5,
									colors[colors.size() - 5].getTopLeft().second - 5 };
					menu_selected_br = { colors[colors.size() - 5].getBtmRight().first - 5,
									colors[colors.size() - 5].getBtmRight().second + 5 };
					break;
				}
			}
			++i;
		}
		return;
	}

	if (draw_mode == 2)
	{
		if (!bc_selection_mode)
		{
			BezierCurve bc;
			bc.addControlPoint(x, y);
			ColorRGB c = colors[col_idx].getColor();
			bc.changeColor(c.red, c.green, c.blue);
			beziers.push_back(bc);
			bc_selection_mode = true;
		}
		else
		{
			beziers[beziers.size() - 1].addControlPoint(x, y);
		}
		return;

	}
	if (draw_mode == 3)
	{
		if (!sc_selection_mode)
		{
			BSplineCurve sc;
			sc.changeK(sc_k_val);
			sc.addControlPoint(x, y);
			ColorRGB c = colors[col_idx].getColor();
			sc.changeColor(c.red, c.green, c.blue);
			splines.push_back(sc);
			sc_selection_mode = true;
		}
		else
		{
			splines[splines.size() - 1].addControlPoint(x, y);
		}
		return;

	}
	if (FILL_MODE == 1)
	{
		floodFill(x, y, pointColor(x, y), colors[col_idx].getColor());
		return;
	}

	if (pt == 1)
	{
		if (draw_mode == 0)
		{
			shapes.push_back(Shape(0, ++shape_number));
			shapes[shape_number].Line::setPoint1(x, y);
		}
		else if (draw_mode == 1)
		{
			shapes.push_back(Shape(1, ++shape_number));
			shapes[shape_number].Circle::setPoint1(x, y);
		}
		ColorRGB c = colors[col_idx].getColor();
		shapes[shape_number].changeColor(c.red, c.green, c.blue);
		shapes[shape_number].changeColorEP(c.red, c.green, c.blue);
	}
	else if (pt == 2)
	{
		if (draw_mode == 0)
		{
			shapes[shape_number].Line::setPoint2(x, y);
		}

		else if (draw_mode == 1)
			shapes[shape_number].Circle::setPoint2(x, y);
	}
}
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouse_x = xpos - 600;
	mouse_y = 400 - ypos;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (glfwGetWindowAttrib(window, GLFW_HOVERED))
	{

		// set point 1 on left click, or set the center
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			set_points(window, 1);

		// set point 2 on right click, or set a point on the circle boundary
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
			if (shapes.empty()) return;
			if (shapes[shape_number].type == 0)if (!shapes[shape_number].Line::first_set) return;
			if (shapes[shape_number].type == 1)if (!shapes[shape_number].Circle::first_set) return;
			set_points(window, 2);
		}
	}
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		// start drawing circles
		FILL_MODE = 0;
		draw_mode = 1;
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		// start drawing lines
		FILL_MODE = 0;
		draw_mode = 0;
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		// stop choosing pts for bezier curves
		FILL_MODE = 0;
		draw_mode = 2;
		if (bc_selection_mode)
		{
			bc_selection_mode = false;
			if (!beziers.empty())
				beziers[beziers.size() - 1].cont_pt_chosen = true;
		}
	}
	if (key == GLFW_KEY_3 || key == GLFW_KEY_2 || key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		// stop choosing pts for bezier curves
		FILL_MODE = 0;
		draw_mode = 3;

		if (key == GLFW_KEY_3) sc_k_val = 4;
		else if (key == GLFW_KEY_2) sc_k_val = 3;
		else if (key == GLFW_KEY_1) sc_k_val = 2;

		if (sc_selection_mode)
		{
			sc_selection_mode = false;
			if (!splines.empty())
				splines[splines.size() - 1].exitEditMode();
		}
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		/*if (bc_selection_mode)
		{
			beziers[beziers.size() - 1].removeControlPoint();
			return;
		}*/
		// delete recent most shape
		if (shapes.empty()) return;

		shapes.pop_back();
		shape_number--;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		// change style of shape
		if (shapes.empty()) return;
		MENUS::edit_style();
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		// Flood fill mode
		std::cout << "\n-> FLOOD FILL" << std::endl;
		FILL_MODE = 1;
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		if (transformation == 0)
		{
			std::cout << "TRANSLATION MODE" << std::endl;
			transformation = 1;
		}
		else
		{
			horiz = 0;
			vert = 0;
			transformation = 0;
			std::cout << "-\n" << std::endl;
		}
	}
	if (transformation == 1)
	{
		// pass arrow keys
		translation_kb(key, action);
	}
	// ROTATION
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		if (transformation == 0)
		{
			std::cout << "ROTATION MODE" << std::endl;
			transformation = 2;
		}
		else
		{
			original_set = false;
			pivot_set = false;
			angle = 0;
			angle_change = 0;
			transformation = 0;

			std::cout << "-\n" << std::endl;
		}
	}
	if (transformation == 2)
	{
		// pass arrow keys
		rotation_kb(key, action);
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		if (transformation == 0)
		{
			std::cout << "SCALING MODE" << std::endl;
			transformation = 3;
		}
		else
		{
			sx = 1;
			sy = 1;
			std::cout << "-\n" << std::endl;
		}
	}
	if (transformation == 3)
	{
		// pass arrow keys
		scaling_kb(key, action);
	}
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (transformation == 0)
	{
		int th = shapes[shape_number].getThickness() + yoffset;
		if (th < 1)th = 1;
		shapes[shape_number].changeThickness(th);
		return;
	}

}
int main()
{
	shapes.reserve(100);
	// for (auto& b : board) b.resize(501, -1);

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Lilac", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) std::cout << "ERROR!" << std::endl;

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-600, 600, -400, 400, 0.0, 1.0);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSwapInterval(1);

	int start_x = (-WIDTH/2) + 15, start_y = (HEIGHT / 2) - 78;// btns are 30 px tall and wide, 5 px spacing bw them.

	for (int i = 0; i < col_vals.size(); ++i)
	{
		colors.push_back(Button(start_x, start_y, start_x + 30, start_y - 30, col_vals[i]));
		start_x += 35;
		if ((i + 1) % 5 == 0)
		{
			start_x = (-WIDTH / 2) + 15;
			start_y -= 35;
		}
	}
	col_idx = colors.size() - 5;
	selected_tl = { colors[colors.size() - 5].getTopLeft().first + 5,
					colors[colors.size() - 5].getTopLeft().second - 5 };
	selected_br = { colors[colors.size() - 5].getBtmRight().first - 5,
					colors[colors.size() - 5].getBtmRight().second + 5 };


	int menu_start_x = -390, menu_start_y = 390;

	for (int i = 0; i < 6; ++i)
	{
		modes.push_back(Button(menu_start_x, menu_start_y, menu_start_x + 100, menu_start_y - 40, col_vals[54]));
		menu_start_x += 120;
	}

	menu_selected_tl = { modes[0].getTopLeft().first + 5,
					modes[0].getTopLeft().second - 5 };
	menu_selected_br = { modes[0].getBtmRight().first - 5,
					modes[0].getBtmRight().second + 5 };


	/*cimg_library::CImg<unsigned char> image("D:\\dev\\OpenGL\\Lilac\\Lilac\\Source\\img\\test.png");
	unsigned char* ptr = image.data(10, 10); // get pointer to pixel @ 10,10
	unsigned char pixel = *ptr;
	std::cout << pixel << std::endl;*/


	// MENUS::show_kb_options();

	glClearColor(w.bg_color[0], w.bg_color[1], w.bg_color[2], w.bg_color[3]);

	/*std::cout << "TRANSLATION: Press T" << std::endl;
	std::cout << "ROTATION: Press R" << std::endl;
	std::cout << "SCALING: Press X\n" << std::endl;*/

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		glPointSize(w.ax_size);
		glBegin(GL_LINES);
		glColor3d(w.ax_color[0], w.ax_color[1], w.ax_color[2]);
		glVertex2d(-800, HEIGHT / 2 - 60);
		glVertex2d(800, HEIGHT / 2 - 60);
		glEnd();

		glPointSize(w.ax_size);
		glBegin(GL_LINES);
		glColor3d(w.ax_color[0], w.ax_color[1], w.ax_color[2]);
		glVertex2d(-400, 340);
		glVertex2d(-400, -400);
		glEnd();

		glPointSize(w.ax_size);
		glBegin(GL_LINES);
		glColor3d(w.ax_color[0], w.ax_color[1], w.ax_color[2]);
		glVertex2d(400, 340);
		glVertex2d(400, -400);
		glEnd();

		// translation
		if (!shapes.empty() && transformation == 1 && (vert || horiz))
			shapes[shape_number].Translate(horiz, vert);

		// rotation
		if (!shapes.empty() && transformation == 2)
			rotate_shape();

		// scaling
		if (!shapes.empty() && transformation == 3)
			scale_shape();

		for (auto sh : shapes)
		{
			if (sh.type == 0)
			{
				if (sh.Line::first_set) sh.Line::setPoint2(mouse_x, mouse_y);
				if (sh.Line::pts_set) draw_line(sh);
			}
			else
			{
				if (sh.Circle::first_set) sh.Circle::setPoint2(mouse_x, mouse_y);
				if (sh.Circle::pts_set) draw_circle(sh);
			}
		}
		for (auto& bz : beziers) drawBezierCurve(bz);
		for (auto& sp : splines) drawBSplineCurve(sp);
		for (auto& blah : board)
			putPoint(blah.first.first, blah.first.second, blah.second);

		glBegin(GL_QUADS);
		glColor3d(0.976, 0.968, 0.862);
		glVertex2i(-WIDTH / 2, HEIGHT / 2 + 40);
		glVertex2i(WIDTH / 2, HEIGHT / 2 + 40);
		glVertex2i(-WIDTH / 2, WIDTH / 2);
		glVertex2i(WIDTH / 2, WIDTH / 2);
		glEnd();

		for (auto& btn : colors)
			btn.drawButton();
		for (auto& btn : modes)
			btn.drawButton();
		showClicked();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}