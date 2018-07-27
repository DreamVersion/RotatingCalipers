#include <iostream>

#include "RotatingCalipers.h"

int main()
{
//    vector<Point> rect;
//    Point left_down(0, 0);
//    Point left_top(0, 4);
//    Point right_top(4, 4);
//    Point right_down(4, 0);
//    rect.push_back(left_down);
//    rect.push_back(left_top);
//    rect.push_back(right_top);
//    rect.push_back(right_down);
//    cout << RotatingCalipers::diameter(rect) << endl;
//    cout << RotatingCalipers::minAreaRect(rect) << endl;

    vector<Point> pts;
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int x = rand() % 1000;
        int y = rand() % 1000;
        cout << "(" << x << "," << y << ")," << endl;
        Point random_pt;
        random_pt.x = x;
        random_pt.y = y;
        pts.push_back(random_pt);
    }
            
    double diameter = RotatingCalipers::diameter(pts);
    MinAreaRect res = RotatingCalipers::minAreaRect(pts);
    return 0;
}