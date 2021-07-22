#include "point2d.h"

Point2d::Point2d(double x, double y) : m_x(x), m_y(y) {}

void Point2d::print()
{
    std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
}

double Point2d::distanceTo(Point2d &point) const
{
    return std::sqrt((m_x - point.m_x) * (m_x - point.m_x) + (m_y - point.m_y) * (m_y - point.m_y));
}

double distanceFrom(Point2d &a, Point2d &b)
{
    return std::sqrt((a.m_x - b.m_x) * (a.m_x - b.m_x) + (a.m_y - b.m_y) * (a.m_y - b.m_y));
}