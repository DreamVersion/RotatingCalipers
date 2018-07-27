//
// Created by melonqi on 2018/7/25.
//

#ifndef MABB_ROTATINGCALIPERS_H
#define MABB_ROTATINGCALIPERS_H

#include <vector>
#include <cmath>

using namespace std;

struct Point
{
    double x;
    double y;

    Point(double _x, double _y) : x(_x), y(_y) {}

    Point() : x(0.0), y(0.0) {}

    bool operator<(const Point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
};

struct MinAreaRect
{
    double width;
    double height;
    double area;
    double angle_width;
    double angle_height;
    Point center;
    Point corner;
    Point vector_width;
    Point vector_height;
    vector<Point> rect;
};

class RotatingCalipers
{
    struct MinAreaState
    {
        size_t bottom;
        size_t left;
        double height;
        double width;
        double base_a;
        double base_b;
        double area;
    };
public:
    //the distance of point to the line, which describes by start and end
    static double _distance(const Point &start, const Point &end, const Point &point);

    static inline double cross(const Point &O, const Point &A, const Point &B)
    {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    static vector<Point> convexHull(vector<Point> p);

    static inline double area(const Point &a, const Point &b, const Point &c)
    {
        return fabs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
    }

    static inline double dist(const Point &a, const Point &b)
    {
        return hypot(a.x - b.x, a.y - b.y);
    }

    static double diameter(const vector<Point> &p);

    static MinAreaRect minAreaRect(const vector<Point> &p);
};


#endif //MABB_ROTATINGCALIPERS_H
