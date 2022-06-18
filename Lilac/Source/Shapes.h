#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// DefaultLine class
class DefaultLine
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

class Line : virtual public DefaultLine
{
protected:
    std::pair<int, int> P1; // X1, Y1
    std::pair<int, int> P2; // X2, Y2

public:
    bool first_set = false;
    bool pts_set = false;

    // constructors
    Line() {}
    Line(int x1, int y1, int x2, int y2, GLdouble r, GLdouble g, GLdouble b, std::string s) : P1(x1, y1), P2(x2, y2) { default_color = { r, g, b }; default_style = s; }

    // set methods
    void setPoint1(int, int);
    void setPoint2(int, int);

    // get methods
    std::pair<int, int> getPoint1();
    std::pair<int, int> getPoint2();


    // end point drawing algo
    void drawEndPoints();

    void Translate(int x, int y)
    {
        P1.first += x;
        P1.second += y;

        P2.first += x;
        P2.second += y;
    }
    void Rotate(int x, int y, float theta, std::pair<int, int> orig1, std::pair<int, int> orig2)
    {
        float Cos = cos(theta), Sin = sin(theta);

        int a = orig1.first, b = orig1.second;

        P1.first = a * Cos - b * Sin + x - x * Cos + y * Sin;
        P1.second = a * Sin + b * Cos + y - y * Cos - x * Sin;

        a = orig2.first, b = orig2.second;

        P2.first = a * Cos - b * Sin + x - x * Cos + y * Sin;
        P2.second = a * Sin + b * Cos + y - y * Cos - x * Sin;
    }
    void Scale(float x, float y)
    {
        P1.first *= x;
        P1.second *= y;

        P2.first *= x;
        P2.second *= y;
    }
};

class Circle : virtual public DefaultLine
{
protected:
    std::pair<int, int> P1; // X1, Y1: center coords
    int radius = 0;

public:
    bool first_set = false;
    bool pts_set = false;

    // constructors
    Circle() {}
    Circle(int x1, int y1, int x2, int y2, GLdouble r, GLdouble g, GLdouble b, std::string s) : P1(x1, y1)
    {
        radius = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
        default_color = { r, g, b };
        default_style = s;
    }

    // set points
    void setPoint1(int x1, int y1);
    void setPoint2(int x2, int y2);

    // get points
    std::pair<int, int> getPoint1();

    // end point drawing algo
    void drawEndPoints();

    void Translate(int x, int y)
    {
        P1.first += x;
        P1.second += y;
    }
    void Rotate(int x, int y, float theta, std::pair<int, int> orig1)
    {
        float Cos = cos(theta), Sin = sin(theta);

        int a = orig1.first, b = orig1.second;

        P1.first = a * Cos - b * Sin + x - x * Cos + y * Sin;
        P1.second = a * Sin + b * Cos + y - y * Cos - x * Sin;

    }
    void Scale(float x, float y)
    {
        P1.first *= x;
        P1.second *= y;
    }
};

class Shape :public Line, public Circle
{
public:
    int type; // 0: line, 1: circle
    int number;
    bool drawn = false;


    void Translate(int x, int y)
    {
        if (type == 0)
        {
            if (!Line::pts_set) return;
            Line::Translate(x, y);
        }
        else
        {
            if (!Circle::pts_set) return;
            Circle::Translate(x, y);
        }
    }
    void Rotate(int x, int y, float theta, std::pair<int, int> orig1, std::pair<int, int> orig2 = { 0,0 })
    {
        if (type == 0)
        {
            if (!Line::pts_set) return;
            Line::Rotate(x, y, theta, orig1, orig2);
        }
        else
        {
            if (!Circle::pts_set) return;
            Circle::Rotate(x, y, theta, orig1);
        }
    }
    void Scale(float sx, float sy)
    {
        if (sx == 0 || sy == 0) return;
        if (type == 0)
        {
            if (!Line::pts_set) return;
            Line::Scale(sx, sy);
        }
        else
        {
            if (!Circle::pts_set) return;
            Circle::Scale(sx, sy);
        }
    }

    // constructors
    Shape() { type = 0; number = -1; }
    Shape(int t, int n) :type(t), number(n) {};
    Shape(int x1, int y1, int x2, int y2, GLdouble r, GLdouble g, GLdouble b, std::string s)
    {
        type = 0;
        Line::P1 = std::make_pair(x1, y1);
        Line::P2 = std::make_pair(x2, y2);
        default_color = { r, g, b };
        default_style = s;
    }
    Shape(int x1, int y1, int rad, GLdouble r, GLdouble g, GLdouble b, std::string s)
    {
        type = 1;
        Circle::P1 = std::make_pair(x1, y1);
        radius = rad;
        default_color = { r, g, b };
        default_style = s;
    }

    // methods
    void display_props();

    // friend functions
    friend void bresenham_circle(Shape&);
    friend void drawOctants(Shape&, int, int);
    friend void draw_circle(Shape&);
    friend void bresenham_line(Shape&);
    friend void draw_line(Shape&);
    //friend void scanlineFill(ColorRGB);
};
struct PolynomialBC
{
    int bin_coeff;
    int one_minus_t_pow;
    int t_pow;
    std::pair<int, int> point;

    PolynomialBC() : bin_coeff(0), one_minus_t_pow(0), t_pow(0), point({ 0, 0 }) {};
    PolynomialBC(int bc, int om_tp, int tp, int x, int y) :bin_coeff(bc), one_minus_t_pow(om_tp), t_pow(tp), point({ x,y }) {}
};
class BezierCurve
{
    std::list<PolynomialBC> equation;
    std::vector<GLdouble> color = { 0.0, 0.0, 0.0 };

public:
    bool cont_pt_chosen = false;

    BezierCurve() {}
    BezierCurve(PolynomialBC p) { equation.push_back(p); }
    BezierCurve(std::list<PolynomialBC>& p) { equation.assign(p.begin(), p.end()); }
    BezierCurve(std::vector<std::pair<int, int>> cont_pts, std::vector<GLdouble> col)
    {
        for (auto& cp : cont_pts)
            addControlPoint(cp.first, cp.second);

        color[0] = col[0];
        color[1] = col[1];
        color[2] = col[2];
    }

    void addControlPoint(int x, int y);
    //void removeControlPoint();
    void changeColor(GLdouble, GLdouble, GLdouble);

    friend void drawBezierCurve(BezierCurve&, int);
};
class BSplineCurve
{

    int n = 0; // no control pts to begin with
    int k = 1; // default degree = 0;
    int chosenK = 1;

    std::vector<int> t; // knot values

    std::vector<std::pair<int, int>> cp; // control points
    std::vector<std::pair<int, int>> seg; // segment end points

    std::vector<BezierCurve> bcs;

    std::vector<GLdouble> color = { 0.0, 0.0, 0.0 };


public:
    bool cont_pt_chosen = false;

    BSplineCurve() {}
    BSplineCurve(int ck) :chosenK(k) {}

    void changeK(int new_ck);
    void addControlPoint(int x, int y);
    //void removeControlPoint();
    void changeColor(GLdouble, GLdouble, GLdouble);
    void exitEditMode();

    friend void drawBSplineCurve(BSplineCurve&);
};