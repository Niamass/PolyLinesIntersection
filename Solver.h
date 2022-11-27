#pragma once
#include <vector>


struct Point 
{
	long long x, y;
};


//ax + by + c = 0, b >= 0
class Line 
{
private:
	long long a, b, c;
public:
	Line() {};
	Line(long long _a, long long _b, long long _c);
	long long getValue(Point) const;
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