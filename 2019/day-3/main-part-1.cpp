#include <cmath>
#include "limits.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

class Point {
public:
	int x_pos;
	int y_pos;
	Point(int,int);
	//manhattan distance
	int distance_to(void) { return std::abs(x_pos) + std::abs(y_pos); }
	bool operator==(const Point&);
	bool operator!=(const Point&);
};

Point::Point(int x, int y)
{
	x_pos = x;
	y_pos = y;	
}

bool Point::operator==(const Point& a) {
	return x_pos==a.x_pos
	&& y_pos==a.y_pos;
}

bool Point::operator!=(const Point& a) {
	return x_pos!=a.x_pos
	|| y_pos!=a.y_pos;
}

//-----------------------------------------------------------------------------

class Instruction {
public:
	char direction;
	int length;
	Instruction(char,int);
};

Instruction::Instruction(char d, int l) {
	direction = d;
	length = l;
}

//-----------------------------------------------------------------------------

void get_input(std::vector<std::string>& input, int which_line)
{
	//skips to selected line
	std::ifstream infile("input.txt");
	for (int i = 0; i < which_line; ++i)
		infile.ignore(std::numeric_limits
			     <std::streamsize>::max(), '\n');
	//reads line into temp variable, and variable into stringstream
	//to process into elements of vector
	std::string a;
	std::getline(infile, a);
	std::stringstream ss(a);
	std::string value;
	while (std::getline(ss, value, ','))
		input.push_back(value);	
	return;
}

//-----------------------------------------------------------------------------

Instruction to_instruction(std::string input) {
	std::stringstream ss(input);
	char direction;
	int length;
	ss >> direction;
	ss >> length;
	return Instruction(direction,length);
}

//-----------------------------------------------------------------------------

//arguments: wire written to, instruction, location of last point
void to_segment(std::vector<Point>& wire, Instruction i, Point& last)
{
	for (int j = 0; j < i.length; ++j) { 
		switch (i.direction) {
			case 'R':
			++last.x_pos;
			break;
		case 'D':
			--last.y_pos;
			break;
		case 'L':
			--last.x_pos;
			break;
		case 'U':
			++last.y_pos;
			break;
		}
		wire.push_back(last);
	}
	return;
}

//-----------------------------------------------------------------------------

int main()
{
	std::vector<std::string> line;
	get_input(line,0);
	std::vector<Point> wire0;
	Point last(0,0);
	for (auto i : line)
		to_segment(wire0,to_instruction(i),last);

	line.clear();
	get_input(line,1);
	std::vector<Point> wire1;
	last.x_pos = 0;
	last.y_pos = 0;
	for (auto i : line)
		to_segment(wire1,to_instruction(i),last);
	
	Point origin(0,0);
	int lowest = INT_MAX;
	std::vector<Point> intersections;
	for (int i = 0; i < wire0.size(); ++i)
		for (int j = 0; j < wire1.size(); ++j)
			if (wire0[i] == wire1[j])
				intersections.push_back(wire0[i]);
	for (int i = 0; i < intersections.size(); ++i)
		if (intersections[i] != origin && intersections[i].distance_to() <= lowest)
			lowest = intersections[i].distance_to();
	std::cout << "Distance to closest intersection: " << lowest << '\n';
	return 0;
}
