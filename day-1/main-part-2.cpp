#include <iostream>
#include <fstream>
#include <string>

int calculate_fuel(int mass, int old)
{
	//set result to old result so we don't lose it
	int result = old;
	//integer division always truncates
	mass = mass / 3 - 2;
	if (mass > 0) {
		result += mass;
		calculate_fuel(mass,result);
	}
	else
		return result;
}

//-----------------------------------------------------------------------------

int main()
{
	int total_fuel_needed = 0;
	int a;
	std::ifstream infile("input.txt");
	while (infile >> a)
		total_fuel_needed += calculate_fuel(a,0);
	std::cout << "Total fuel needed: " << total_fuel_needed << '\n';
	return 0;
}
