#include "Shapes.h"
#include "WindowProperties.h"

void printColorPresets();

/* IMPLEMENTATION OF WINDOW PROPERTIES */
void Window::change_bgCol(GLdouble r, GLdouble g, GLdouble b, GLdouble a)
{
    bg_color[0] = r; bg_color[1] = g; bg_color[2] = b; bg_color[3] = a;
}
void Window::change_axCol(GLdouble r, GLdouble g, GLdouble b)
{
    ax_color[0] = r; ax_color[1] = g; ax_color[2] = b;
}
void Window::change_orgCol(GLdouble r, GLdouble g, GLdouble b)
{
    org_color[0] = r; org_color[1] = g; org_color[2] = b;
}
void Window::change_axsize(int s) { ax_size = s; }
void Window::change_orgsize(int s) { org_size = s; }
void Window::change_ColPresets(int i)
{
    // 0 bg, 1 ax, 2 org
    int choice;

    printColorPresets();

    std::cin >> choice;

    if (choice == 1)
    {
        if (i == 0) change_bgCol(0.0, 0.0, 1.0, 1.0);
        else if (i == 1) change_axCol(0.0, 0.0, 1.0);
        else change_orgCol(0.0, 0.0, 1.0);
    }
    else if (choice == 2)
    {
        if (i == 0) change_bgCol(0.0, 1.0, 0.0, 1.0);
        else if (i == 1) change_axCol(0.0, 1.0, 0.0);
        else change_orgCol(0.0, 1.0, 0.0);
    }
    else if (choice == 3)
    {
        if (i == 0) change_bgCol(1.0, 0.0, 0.0, 1.0);
        else if (i == 1) change_axCol(1.0, 0.0, 0.0);
        else change_orgCol(1.0, 0.0, 0.0);
    }
    else if (choice == 4)
    {
        if (i == 0) change_bgCol(0.0, 0.0, 0.0, 1.0);
        else if (i == 1) change_axCol(0.0, 0.0, 0.0);
        else change_orgCol(0.0, 0.0, 0.0);
    }
    else if (choice == 5)
    {
        if (i == 0) change_bgCol(1.0, 1.0, 0.0, 1.0);
        else if (i == 1) change_axCol(1.0, 1.0, 0.0);
        else change_orgCol(1.0, 1.0, 0.0);
    }
    else if (choice == 6)
    {
        if (i == 0) change_bgCol(1.0, 0.0, 0.5, 1.0);
        else if (i == 1) change_axCol(1.0, 0.0, 0.5);
        else change_orgCol(1.0, 0.0, 0.5);
    }
    else if (choice == 7)
    {
        if (i == 0) change_bgCol(1.0, 0.5, 0.0, 1.0);
        else if (i == 1) change_axCol(1.0, 0.5, 0.0);
        else change_orgCol(1.0, 0.5, 0.0);
    }
    else if (choice == 8)
    {
        if (i == 0) change_bgCol(0.0, 0.75, 1.0, 1.0);
        else if (i == 1) change_axCol(0.0, 0.75, 1.0);
        else change_orgCol(0.0, 0.75, 1.0);
    }
    else if (choice == 9)
    {
        if (i == 0) change_bgCol(0.5, 0.0, 1.0, 1.0);
        else if (i == 1) change_axCol(0.5, 0.0, 1.0);
        else change_orgCol(0.5, 0.0, 1.0);
    }
}

/* IMPLEMENTATION OF DEFAULT LINE PROPERTIES */
void DefaultLine::display_props(int t)
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
void DefaultLine::changeColor(GLdouble r, GLdouble g, GLdouble b)
{
    default_color[0] = r;
    default_color[1] = g;
    default_color[2] = b;
}
void DefaultLine::changeColorPresets()
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
void DefaultLine::changeThickness(int t)
{
    default_thickness = t;
}
void DefaultLine::changeStyle(std::string s)
{
    default_style = s;
}
void DefaultLine::changeStylePresets()
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
void DefaultLine::changeColorEP(GLdouble r, GLdouble g, GLdouble b)
{
    default_ep_color[0] = r;
    default_ep_color[1] = g;
    default_ep_color[2] = b;
}
void DefaultLine::changeColorEPPresets()
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
void DefaultLine::changeSizeEP(int s)
{
    default_ep_size = s;
}
int DefaultLine::getThickness()
{
    return default_thickness;
}
/* IMPLEMENTATION OF LINE PROPERTIES */
void Line::setPoint1(int x1, int y1)
{
    P1.first = x1;
    P1.second = y1;
    first_set = true;
}
void Line::setPoint2(int x2, int y2)
{
    P2.first = x2;
    P2.second = y2;
    pts_set = true;
    first_set = false;
}
void Line::drawEndPoints()
{
    glPointSize(default_ep_size);
    glBegin(GL_POINTS);
    glColor3d(default_ep_color[0], default_ep_color[1], default_ep_color[2]);
    glVertex2i(P1.first, P1.second);
    glEnd();

    if (pts_set)
    {
        glPointSize(default_ep_size);
        glBegin(GL_POINTS);
        glColor3d(default_ep_color[0], default_ep_color[1], default_ep_color[2]);
        glVertex2i(P2.first, P2.second);
        glEnd();
    }
}
std::pair<int, int> Line::getPoint1()
{
    return P1;
}
std::pair<int, int> Line::getPoint2()
{
    return P2;
}
/* IMPLEMENTATION OF CIRCLE PROPERTIES */
void Circle::setPoint1(int x1, int y1)
{
    P1.first = x1;
    P1.second = y1;
    first_set = true;
}
void Circle::setPoint2(int x2, int y2)
{
    radius = sqrt(pow((P1.first - x2), 2) + pow((P1.second - y2), 2));
    pts_set = true;
    first_set = false;
}
std::pair<int, int> Circle::getPoint1()
{
    return P1;
}
void Circle::drawEndPoints()
{
    glPointSize(default_ep_size);
    glBegin(GL_POINTS);
    glColor3d(default_ep_color[0], default_ep_color[1], default_ep_color[2]);
    glVertex2i(P1.first, P1.second);
    glEnd();
}

/* IMPLEMENTATION OF SHAPE PROPERTIES */
void Shape::display_props()
{
    std::cout << "\t\tSHAPE NUMBER: " << number;
    type == 0 ? std::cout << ", is a LINE\n" << std::endl : std::cout << ", is a CIRCLE\n" << std::endl;
    DefaultLine::display_props(type);
}



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
int binomialCoefficient(int n, int k)
{
    std::vector<std::vector<int>> bc(n + 1);
    for (auto& v : bc) v.resize(k + 1);

    for (int i = 0; i <= n; ++i) bc[i][0] = 1;
    for (int i = 0; i <= k; ++i) bc[i][i] = 1;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= k; ++j)
            bc[i][j] = bc[i - 1][j - 1] + bc[i - 1][j];

    return bc[n][k];
}
void BezierCurve::addControlPoint(int x, int y)
{
    std::list<PolynomialBC> eqn;
    std::vector<std::pair<int, int>> coords;
    for (auto& e : equation) coords.push_back(e.point);

    for (int i = 1; i <= equation.size() + 1; ++i)
    {
        if (i <= equation.size())
        {
            eqn.push_back(PolynomialBC(binomialCoefficient(equation.size(), i - 1),
                equation.size() - i + 1,
                i - 1,
                coords[i - 1].first,
                coords[i - 1].second
            ));
        }
        else
        {
            eqn.push_back(PolynomialBC(binomialCoefficient(equation.size(), i - 1),
                equation.size() - i + 1,
                i - 1,
                x, y
            ));
        }
    }
    equation.assign(eqn.begin(), eqn.end());

}
//void BezierCurve::removeControlPoint()
//{
//    if (equation.empty()) return;
//
//    equation.pop_back();
//    std::list<Polynomial> eqn;
//    std::vector<std::pair<int, int>> coords;
//    for (auto& e : equation) coords.push_back(e.point);
//
//    for (int i = 1; i <= equation.size(); ++i)
//    {
//        eqn.push_back(Polynomial(binomialCoefficient(equation.size() - 1 , i),
//            equation.size() - i + 1,
//            i - 1,
//            coords[i - 1].first,
//            coords[i - 1].second
//        ));
//    }
//    equation.assign(eqn.begin(), eqn.end());
//}
void BezierCurve::changeColor(GLdouble r, GLdouble g, GLdouble b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}
void BSplineCurve::changeColor(GLdouble r, GLdouble g, GLdouble b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}
void BSplineCurve::exitEditMode()
{
    cont_pt_chosen = true;
    for (auto& bc : bcs)
        bc.cont_pt_chosen = true;
}
void BSplineCurve::changeK(int new_k)
{
    chosenK = new_k;
}
void BSplineCurve::addControlPoint(int x, int y)
{
    n += 1;
    if (chosenK != k)
    {
        if (n - chosenK + 2 > 0) k = chosenK;
        else k += 1;
    }

    // add the control point
    cp.push_back({ x, y });
    seg.push_back({ x, y });


    bcs.clear();
    // find out the segments: linear, quad and cubic
    if (k == 4) // cubic // no of control points >= 3
    {
        //std::cout << "cubic" << std::endl;
        seg[0] = cp[0];
        for (int i = 1; i < n - 1; ++i)
        {
            seg[i].first = 0.167 * (cp[i - 1].first) + 0.67 * (cp[i].first) + 0.167 * (cp[i + 1].first);
            seg[i].second = 0.167 * (cp[i - 1].second) + 0.67 * (cp[i].second) + 0.167 * (cp[i + 1].second);
        }
        seg[n - 1] = cp[n - 1];

        for (int i = 1; i < n; ++i)
        {
            std::vector<std::pair<int, int>> cont_pts;
            cont_pts.push_back(seg[i - 1]);
            cont_pts.push_back({ (0.67 * (cp[i - 1].first)) + (0.34 * (cp[i].first)),  (0.67 * (cp[i - 1].second)) + (0.34 * (cp[i].second)) });
            cont_pts.push_back({ (0.34 * (cp[i - 1].first)) + (0.67 * (cp[i].first)),  (0.34 * (cp[i - 1].second)) + (0.67 * (cp[i].second)) });
            cont_pts.push_back(seg[i]);

            bcs.push_back(BezierCurve(cont_pts, color));
        }
    }
    else if (k == 3) // quadratic
    {
        //std::cout << "quadratic" << std::endl;
        seg[0] = cp[0];
        for (int i = 1; i < n - 1; ++i)
        {
            seg[i].first = 0.25 * (cp[i - 1].first) + 0.5 * (cp[i].first) + 0.25 * (cp[i + 1].first);
            seg[i].second = 0.25 * (cp[i - 1].second) + 0.5 * (cp[i].second) + 0.25 * (cp[i + 1].second);
        }
        seg[n - 1] = cp[n - 1];

        for (int i = 1; i < n; ++i)
        {
            std::vector<std::pair<int, int>> cont_pts;
            cont_pts.push_back(seg[i - 1]);
            cont_pts.push_back({ (0.5 * (cp[i - 1].first)) + (0.5 * (cp[i].first)),  (0.5 * (cp[i - 1].second)) + (0.5 * (cp[i].second)) });
            cont_pts.push_back(seg[i]);

            bcs.push_back(BezierCurve(cont_pts, color));
        }
    }
    else if (k == 2) // linear
    {
        //std::cout << "linear" << std::endl;

        for (int i = 1; i < n; ++i)
        {
            std::vector<std::pair<int, int>> cont_pts;
            cont_pts.push_back(cp[i - 1]);
            cont_pts.push_back(cp[i]);

            bcs.push_back(BezierCurve(cont_pts, color));
        }
    }



}
