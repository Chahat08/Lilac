#pragma once
#include <iostream>
#include <vector>
#include "Shapes.h"

struct ColorRGB
{
	GLfloat red, green, blue;

	ColorRGB() : red(0), green(0), blue(0) {}
	ColorRGB(float r, float g, float b) : red(r), green(g), blue(b) {}

	bool operator==(ColorRGB c)
	{
		int r1 = red * 100, g1 = green * 100, b1 = blue * 100;
		int r2 = c.red * 100, g2 = c.green * 100, b2 = c.blue * 100;
		return r1 == r2 && g1 == g2 && b1 == b2;
	}
	bool operator!=(ColorRGB c)
	{
		return !operator==(c);
	}
} pixel;
class Button
{
private:
	std::pair<int, int> top_left;
	std::pair<int, int> btm_right;

	ColorRGB color;
public:
	bool clicked = false;

	//Constructors
	Button() :top_left({ 0, 0 }), btm_right({ 0,0 }), color(0.0, 0.0, 0.0) {}
	Button(int l1, int l2, int r1, int r2) : top_left({ l1, l2 }), btm_right({ r1, r2 }), color(0.0, 0.0, 0.0) {}
	Button(int l1, int l2, int r1, int r2, double r, double g, double b) : top_left({ l1, l2 }), btm_right({ r1, r2 }), color(r, g, b) {}
	Button(int l1, int l2, int r1, int r2, ColorRGB c) : top_left({ l1, l2 }), btm_right({ r1, r2 }), color(c) {}

	// button rendering
	void drawButton();

	//setting methods
	//void setColor(double r, double g, double b) { color = { r, g, b }; }
	void setColor(ColorRGB c) { color = c; }

	// getting methods
	std::pair<int, int> getTopLeft()
	{
		return top_left;
	}
	std::pair<int, int> getBtmRight()
	{
		return btm_right;
	}
	ColorRGB getColor()
	{
		return color;
	}
};

void Button::drawButton()
{
	glBegin(GL_QUADS);
	glColor3d(color.red, color.green, color.blue);
	glVertex2i(top_left.first, top_left.second);
	glVertex2i(top_left.first, btm_right.second);
	glVertex2i(btm_right.first, btm_right.second);
	glVertex2i(btm_right.first, top_left.second);
	glEnd();

	glFlush();
}

