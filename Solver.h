#pragma once
#include <vector>


struct Point 
{
	int x, y;
};


//ax + by + c = 0, b >= 0
class Line 
{
private:
	int a, b, c;
public:
	Line() {};
	Line(int _a, int _b, int _c);
	int getValue(Point) const;
};

class Solver 
{
private:
	int i_left, i_right; //"сама€ лева€" и "сама€ права€" точки многоугольника
	std::vector<Point> polygon;

	int TernarySearchMin(const Line &, int, int) const;
	int TernarySearchMax(const Line &, int, int) const;
	std::vector<int> BinarySearch(const Line &, int, int) const;
public:
	Solver(const std::vector<Point>&);
	std::vector<int> isIntersect(const Line &) const;
};