#include "Solver.h"

Line::Line(int _a, int _b, int _c)
{
	if (_b < 0)
	{
		a = -_a;
		b = -_b;
		c = -_c;
	}
	else
	{ 
		a = _a;
		b = _b;
		c = _c;
	}
}


// "расстояние", может быть отрицательным
int Line::getValue(Point point) const
{
	return a * point.x + b * point.y + c;
}


Solver::Solver(const std::vector<Point>& _polygon)
{
	// Определение границ "верхней" и "нижней" частей многоугольника
	polygon = _polygon;
	int max = polygon[0].x, min = polygon[0].x;
	int i_max = 0, i_min = 0;
	for (int i = 0; i < polygon.size(); i++)
	{
		if (polygon[i].x > max)
		{
			max = polygon[i].x;
			i_max = i;
		}

		if (polygon[i].x < min)
		{
			min = polygon[i].x;
			i_min = i;
		}			
	}
	i_left = i_min;
	i_right = i_max;
}

int Solver::TernarySearchMin(const Line & line, int start, int finish) const
{
	int m1, m2, N = polygon.size();
	if (start > finish)
		finish = N + finish;

	while (finish - start > 2)
	{
		m1 = start + (finish - start) / 3;
		m2 = finish - (finish - start) / 3;
		if (line.getValue(polygon[m1 % N]) > line.getValue(polygon[m2 % N]))
			start = m1;
		else
			finish = m2;
	}

	int val_start = line.getValue(polygon[start % N]);
	int val_med = line.getValue(polygon[(start + 1) % N]);
	int val_finish = line.getValue(polygon[finish % N]);
	if (val_start <= val_med)
		if (val_start <= val_finish)
			return start % N;
		else
			return finish % N;
	else if (val_med <= val_finish)
		return (start + 1) % N;
	else return finish % N;
}

int Solver::TernarySearchMax(const Line & line, int start, int finish) const
{
	int m1, m2, N = polygon.size();
	if (start > finish)
		finish = N + finish;
	
	while (finish - start > 2)
	{
		m1 = start + (finish - start) / 3;
		m2 = finish - (finish - start) / 3;
		if (line.getValue(polygon[m1 % N]) < line.getValue(polygon[m2 % N]))
			start = m1;
		else
			finish = m2;
	}
	
	int val_start = line.getValue(polygon[start % N]);
	int val_med = line.getValue(polygon[(start + 1) % N]);
	int val_finish = line.getValue(polygon[finish % N]);
	if (val_start >= val_med)
		if (val_start >= val_finish)
			return start % N;
		else
			return finish % N;
	else if (val_med >= val_finish)
		return (start + 1) % N;
	else return  finish % N;
}

std::vector<int> Solver:: BinarySearch(const Line & line, int start, int finish) const
{
	std::vector<int> answer;
	int med, val_med, N = polygon.size();
	int val_start = line.getValue(polygon[start]);
	int val_finish = line.getValue(polygon[finish]);
	if (start > finish)
		finish = N + finish;

	while (finish - start > 1)
	{
		med = (start + finish) / 2;
		val_med = line.getValue(polygon[med % N]);
		if (val_med * val_start < 0)
		{
			finish = med;
			val_finish = val_med;
		}
		else if (val_med * val_finish < 0)
		{
			start = med;
			val_start = val_med;
		}
		else
		{
			answer.push_back(med % N);
			return answer;
		}
	}

	answer.push_back(start % N);
	answer.push_back(finish % N);
	return answer;
}

std::vector<int> Solver::isIntersect(const Line & line) const
{	
	int max, min, N = polygon.size();
	std::vector<int> answer;
	
	max = TernarySearchMax(line, i_right, i_left); //индекс точки с максимумом расстояния в "верхней" части
	min = TernarySearchMin(line, i_left, i_right); //индекс точки с минимумом расстояния в "нижней" части

	int val_max = line.getValue(polygon[max]);
	int val_min = line.getValue(polygon[min]);

	if (val_max * val_min < 0)
	{	
		//случай пересечения
		auto ans1 = BinarySearch(line, max, min);// пересечение в "левой" части
		auto ans2 = BinarySearch(line, min, max);// пересечение в "правой" части
		if (ans1.size() < ans2.size())
		{
			ans2.insert(ans2.end(), ans1.begin(), ans1.end());
			return ans2;
		}
		else
		{
			ans1.insert(ans1.end(), ans2.begin(), ans2.end());
			return ans1;
		} 
	}
	else if (val_max == 0)
	{
		//случай касания
		answer.push_back(max);
		if (line.getValue(polygon[(max + 1) % N]) == 0)
			answer.push_back((max + 1) % N);
		else if (line.getValue(polygon[(max + N - 1) % N]) == 0)
			answer.push_back((max + N - 1) % N);
	}
	else if (val_min == 0)
	{
		//случай касания
		answer.push_back(min);
		if (line.getValue(polygon[(min + 1) % N]) == 0)
			answer.push_back((min + 1) % N);
		else if (line.getValue(polygon[(min + N - 1) % N]) == 0)
			answer.push_back((min + N - 1) % N);
	}

	return answer;
}
