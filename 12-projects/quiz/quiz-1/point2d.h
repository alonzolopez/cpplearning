#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>
#include <cmath>

class Point2d
{
private:
    double m_x;
    double m_y;
public:
    Point2d(double x = 0.0, double y = 0.0);
    void print();
    double distanceTo(Point2d &point) const;
    friend double distanceFrom(Point2d &a, Point2d &b);
};

#endif