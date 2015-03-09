#include "ED.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	std::string s = argv[1];
	std::string t = argv[2];

	ED my_ed(s, t);

	std::cout << my_ed;









	return 0;
}
