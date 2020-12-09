#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

std::vector<int> value;
const int halt = 99;

//-----------------------------------------------------------------------------

void get_values()
{
	int a;
	std::ifstream infile("input-part-2.txt");
	while (infile >> a) {
		value.push_back(a);
		if (infile.peek() == ',')
			infile.ignore();
	}
	return;
}

//-----------------------------------------------------------------------------

int execute_opcode(int opcode, int v1, int v2)
{
	int result = 0;
	switch (opcode) {
		case 1:
			result = v1 + v2;
			break;
		case 2:
			result = v1 * v2;
			break;
	}
	return result;
}

//-----------------------------------------------------------------------------

void calculate()
{
	for (int i = 0; i <= value.size(); i+=4) {
		if (value[i] != halt) {
			//saving write position in temp variable 
			//in case overwritten
			int write_pos = value[i+3];
			//write to position given by 3rd integer
			//result of operation of opcode given by 0th integer, 
			//on operands given by 1st and 2nd integers
			value[write_pos] = 
				execute_opcode(value[i],
					       value[value[i+1]],
					       value[value[i+2]]);
		}
		else
			return;
	}
}

//-----------------------------------------------------------------------------
	
int main()
{
	get_values();
	for (int i = 0; i <= 99; ++i) {
		value[1] = i;
		for (int j = 0; j <= 99; ++j) {
			value[2] = j;
			calculate();
			if (value[0] == 19690720) {
				std::cout << "Result: " << 100 *  value[1] + value[2] << '\n';
				return 0;
			}
			value.clear();
			get_values();
			//super hacky, make sure get_values leaves value[1] alone
			value[1] = i;
		}
	}
	return 0;
}
