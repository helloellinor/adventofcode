#include <iostream>
#include <string>

int main()
{
	int answers = 0;
	for (int i = 138307; i <= 654504; ++i) {
		std::string password = std::to_string(i);
		for (int j = 5; j >= 0; --j)
			if (password[j] < password[j-1])
				for (int k = j; k <= 5; ++k)
			 		password[k] = password[j-1];
		bool consecutive = false;
		for (int j = 5; j >= 0; --j)
			if (password[j] == password[j-1]) {
				consecutive = true;
				break;
			}
		if (consecutive == true) {
			i = std::stoi(password);
			if (i >= 654504)
				break;
			++answers;
		}
	}
	std::cout << "Number of unique passwords: " << answers << '\n';
	return 0;
}	
