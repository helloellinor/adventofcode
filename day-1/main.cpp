#include <iostream>
#include <fstream>
#include <string>

int main()
{
	int a;
	int total_fuel_needed = 0;
	std::ifstream infile("input.txt");
	while (infile >> a)
	{
		//integer division always truncates
		a = a / 3 - 2;
		total_fuel_needed += a;
	}
	std::cout << "Total fuel needed: " << total_fuel_needed << '\n';
	return 0;
}

