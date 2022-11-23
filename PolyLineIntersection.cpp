#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Solver.h"


bool getData(const std::string& inputPath, std::vector<Point>& polygon, std::vector <Line>& lines)
{
	std::ifstream out;
	out.open(inputPath);

	if (out.is_open())
	{
		std::string strPolygon;
		std::string strLine;
		if (!getline(out, strPolygon) || !getline(out, strLine))
		{
			std::cout << "Not enough lines in input" << std::endl;
			return false;
		}

		try {
			bool isSecond = false;
			int x;
			std::string num;
			std::stringstream ssp(strPolygon);
			std::size_t pos;
			while (getline(ssp, num, ' '))
			{
				int tmp = std::stoi(num, &pos);
				if (pos != num.size())
				{
					std::cout << ("Extra chars in int def" + num).data() << std::endl;
					return false;
				}
				if (isSecond)
				{
					polygon.push_back({ x, tmp });
					isSecond = false;
				}
				else
				{
					x = tmp;
					isSecond = true;
				}
			}
			if (isSecond == true)
			{
				std::cout << "Odd number of coordinates" << std::endl;
				return false;
			}
			
			std::vector<int> lineVect;
			do 
			{
				std::stringstream ssl(strLine);
				while (getline(ssl, num, ' '))
				{
					int tmp = std::stoi(num, &pos);
					if (pos != num.size())
					{
						std::cout << ("Extra chars in int def" + num).data() << std::endl;
						return false;
					}
					lineVect.push_back(tmp);
				}

				if (lineVect.size() != 3)
				{
					std::cout << "Not enough ints in line def" << std::endl;
					return false;
				}
				else if (lineVect[0] == 0 && lineVect[1] == 0)
				{
					std::cout << "Incorrect line def" << std::endl;
					return false;
				}
				else
					lines.push_back(Line(lineVect[0], lineVect[1], lineVect[2]));
				lineVect.clear();
			} while (getline(out, strLine));
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << ("Can't open" + inputPath).data() << std::endl;
		return false;
	}
	out.close();
	return true;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 0;

	std::vector <Line> lines;
	std::vector<Point> polygon;

	if (!getData(argv[1], polygon, lines)) 
		return 0;
	else 
	{
		Solver * solver = new Solver(polygon);
		for (int i = 0; i < lines.size(); i++)
		{
			std::vector<int> answer = solver->isIntersect(lines[i]);
			for (int j = 0; j < answer.size(); j++)
				std::cout << answer[j] << " ";
			std::cout <<std::endl;
		}			
	}
	return 0;
}

