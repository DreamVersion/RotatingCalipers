//
// Created by melonqi on 2018/7/25.
//

#include <iostream>
#include "RotatingCalipers.h"

double RotatingCalipers::_distance(const Point &start, const Point &end, const Point &point)
{
    double dist = (point.y - start.y) * (end.x - start.x) - (point.x - start.x) * (end.y - start.y);
    return dist;
}

vector<Point> RotatingCalipers::convexHull(vector<Point> P)
{
    size_t n = P.size();
    size_t k = 0;
    if (n <= 3) return P;

    vector<Point> H(2 * n);
    sort(P.begin(), P.end());

    for (size_t i = 0; i < n; ++i)
    {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }

    for (size_t i = n - 1, t = k + 1; i > 0; --i)
    {
        while (k >= t && cross(H[k - 2], H[k - 1], P[i - 1]) <= 0) k--;
        H[k++] = P[i - 1];
    }
    H.resize(k - 1);
    return H;
}

double RotatingCalipers::diameter(const vector<Point> &p)
{
    vector<Point> h = convexHull(p);
    size_t m = h.size();
    if (1 == m) return 0;
    if (2 == m) return dist(h[0], h[1]);

    size_t k = 1;
    while (area(h[m - 1], h[0], h[(k + 1) % m]) > area(h[m - 1], h[0], h[k])) k++;

    double res = 0;
    for (size_t i = 0, j = k; i <= k && j < m; i++)
    {
        res = max(res, dist(h[i], h[j]));
        while (j < m && area(h[i], h[(i + 1) % m], h[(j + 1) % m]) > area(h[i], h[(i + 1) % m], h[j]))
        {
            res = max(res, dist(h[i], h[(j + 1) % m]));
            j++;
        }
    }
    return res;
}

MinAreaRect RotatingCalipers::minAreaRect(const vector<Point> &p)
{
    vector<Point> points = convexHull(p);
    cout << "convexHull" << endl;
    for (size_t i = 0; i < points.size(); i++)
        cout << "(" << points[i].x << "," << points[i].y << ")," << endl;
    double min_area = numeric_limits<double>::max();
    double max_dist = 0;
    size_t left = 0, bottom = 0, right = 0, top = 0;

    /* rotating calipers sides will always have coordinates
     (a,b) (-b,a) (-a,-b) (b, -a)
     */
    /* this is a first base bector (a,b) initialized by (1,0) */

    Point pt0 = points[0];
    double left_x = pt0.x;
    double right_x = pt0.x;
    double top_y = pt0.y;
    double bottom_y = pt0.y;

    size_t n = points.size();

    vector<Point> vect(n);
    vector<double> inv_vect_length(n);

    for (size_t i = 0; i < n; i++)
    {
        if (pt0.x < left_x)
        {
            left_x = pt0.x;
            left = i;
        }
        if (pt0.x > right_x)
        {
            right_x = pt0.x;
            right = i;
        }
        if (pt0.y > top_y)
        {
            top_y = pt0.y;
            top = i;
        }
        if (pt0.y < bottom_y)
        {
            bottom_y = pt0.y;
            bottom = i;
        }

        Point pt = points[(i + 1) & (i + 1 < n ? -1 : 0)];
        double dx = pt.x - pt0.x;
        double dy = pt.y - pt0.y;

        vect[i].x = dx;
        vect[i].y = dy;

        inv_vect_length[i] = 1. / sqrt(dx * dx + dy * dy);
        pt0 = pt;
    }

    // find convex hull orientation
    double ax = vect[n - 1].x;
    double ay = vect[n - 1].y;
    double orientation = 0, base_a = 0, base_b = 0;

    for (size_t i = 0; i < n; i++)
    {
        double bx = vect[i].x;
        double by = vect[i].y;
        double convexity = ax * by - ay * bx;
        if (convexity != 0)
        {
            orientation = (convexity > 0) ? 1.0 : -1.0;
            break;
        }
        ax = bx;
        ay = by;
    }

    base_a = orientation;

    /*****************************************************************************************/
    /*                         init calipers position                                        */
    size_t seq[4] = {0};
    seq[0] = bottom;
    seq[1] = right;
    seq[2] = top;
    seq[3] = left;

    /*****************************************************************************************/
    /*                         Main loop - evaluate angles and rotate calipers               */

    MinAreaState min_area_state;

    /* all of edges will be checked while rotating calipers by 90 degrees */
    for (size_t k = 0; k < n; k++)
    {
        /* sinus of minimal angle */
        /*float sinus;*/

        /* compute cosine of angle between calipers side and polygon edge */
        /* dp - dot product */
        double dp0 = base_a * vect[seq[0]].x + base_b * vect[seq[0]].y;
        double dp1 = -base_b * vect[seq[1]].x + base_a * vect[seq[1]].y;
        double dp2 = -base_a * vect[seq[2]].x - base_b * vect[seq[2]].y;
        double dp3 = base_b * vect[seq[3]].x - base_a * vect[seq[3]].y;

        double cos_alpha = dp0 * inv_vect_length[seq[0]];
        double max_cos = cos_alpha;
        /* number of calipers edges, that has minimal angle with edge */
        int main_element = 0;

        /* choose minimal angle */
        cos_alpha = dp1 * inv_vect_length[seq[1]];
        max_cos = (cos_alpha > max_cos) ? (main_element = 1, cos_alpha) : max_cos;
        cos_alpha = dp2 * inv_vect_length[seq[2]];
        max_cos = (cos_alpha > max_cos) ? (main_element = 2, cos_alpha) : max_cos;
        cos_alpha = dp3 * inv_vect_length[seq[3]];
        max_cos = (cos_alpha > max_cos) ? (main_element = 3, cos_alpha) : max_cos;

        /*rotate calipers*/
        //get next base
        size_t pindex = seq[main_element];
        double lead_x = vect[pindex].x * inv_vect_length[pindex];
        double lead_y = vect[pindex].y * inv_vect_length[pindex];
        switch (main_element)
        {
            case 0:
                base_a = lead_x;
                base_b = lead_y;
                break;
            case 1:
                base_a = lead_y;
                base_b = -lead_x;
                break;
            case 2:
                base_a = -lead_x;
                base_b = -lead_y;
                break;
            case 3:
                base_a = -lead_y;
                base_b = lead_x;
                break;
        }

        /* change base point of main edge */
        seq[main_element] += 1;
        seq[main_element] = (seq[main_element] == n) ? 0 : seq[main_element];

        double dx = points[seq[1]].x - points[seq[3]].x;
        double dy = points[seq[1]].y - points[seq[3]].y;
        double width = dx * base_a + dy * base_b;
        dx = points[seq[2]].x - points[seq[0]].x;
        dy = points[seq[2]].y - points[seq[0]].y;
        double height = -dx * base_b + dy * base_a;
        double area = width * height;
        if (area <= min_area)
        {
            min_area = area;
            min_area_state.base_a = base_a;//buf[1]
            min_area_state.base_b = base_b;//buf[3]
            min_area_state.width = width;//buf[2]
            min_area_state.height = height;//buf[4]
            min_area_state.left = seq[3];//buf[0]
            min_area_state.bottom = seq[0];//buf[5]
            min_area_state.area = area;//buf[6]
        }
    }


    double A1 = min_area_state.base_a;
    double B1 = min_area_state.base_b;

    double A2 = -min_area_state.base_b;
    double B2 = min_area_state.base_a;

    double C1 = A1 * points[min_area_state.left].x + points[min_area_state.left].y * B1;
    double C2 = A2 * points[min_area_state.bottom].x + points[min_area_state.bottom].y * B2;

    double idet = 1.f / (A1 * B2 - A2 * B1);

    double px = (C1 * B2 - C2 * B1) * idet;
    double py = (A1 * C2 - A2 * C1) * idet;

    Point out0(px, py);
    Point out1(A1 * min_area_state.width, B1 * min_area_state.width);
    Point out2(A2 * min_area_state.height, B2 * min_area_state.height);

    MinAreaRect min_area_rect;
    min_area_rect.corner = out0;
    min_area_rect.vector_width = out1;
    min_area_rect.vector_height = out2;

    min_area_rect.rect.push_back(out0);
    min_area_rect.rect.push_back(Point(out0.x + out1.x, out0.y + out1.y));
    min_area_rect.rect.push_back(Point(out0.x + out1.x + out2.x, out0.y + out1.y + out2.y));
    min_area_rect.rect.push_back(Point(out0.x + out2.x, out0.y + out2.y));

    min_area_rect.center.x = out0.x + (out1.x + out2.x) * 0.5f;
    min_area_rect.center.y = out0.y + (out1.y + out2.y) * 0.5f;
    min_area_rect.width = std::sqrt(out1.x * out1.x + out1.y * out1.y);
    min_area_rect.height = std::sqrt(out2.x * out2.x + out2.y * out2.y);
    min_area_rect.angle_width = atan2(out1.y, out1.x);
    min_area_rect.angle_height = atan2(out2.y, out2.y);

    return min_area_rect;
}
