# RotatingCalipers
Use Rotating Calipers algorithm to compute the diameter or minimum area rect of a set of points.
## Usage: diameter
Use Rotating Calipers to compute the diameter of a set of points. Find two points in the set of points which have the longest distance. Using Rotating Calipers can be faster.  

```
	vector<Point> pts;
	double diameter = RotatingCalipers::diameter(pts);
```

## Usage: min area rect
Minimum area rectangle or oriented minimum bounding box, is to find a rectangle to contains all points;

Use the code in opencv.

```
	vector<Point> pts;
	MinAreaRect res = RotatingCalipers::minAreaRect(its);
``` 

MinAreaRect
```
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
```
![](http://7xpwmi.com1.z0.glb.clouddn.com/obaa.png)
## Usage: convexHull
Because Rotating Calipers is based on convexHull, we achieve the convexHull functions.

```
	vector<Point> pts;
	vector<Point> convex_hull = RotatingCalipers::convexHull(pts);
```
![](http://7xpwmi.com1.z0.glb.clouddn.com/convexHull.png)

## show
We also write python to show whether the result is right. You need to copy the points to the show.py 