#include "ED.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	std::string s = argv[1];
	std::string t = argv[2];

	ED my_ed(s, t);
//	std::cout << my_ed; 
	
	std::cout << std::endl << std::endl;

	my_ed.OptDistance();
	std::cout << my_ed;










	return 0;
}
