#include <SFML/System.hpp>
#include "ED.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	std::string s = argv[1];
	std::string t = argv[2];
	std::string edit_distance_path;

	sf::Clock clock;
	sf::Time time;

	ED my_ed(s,t);

	my_ed.OptDistance();
	std::cout << my_ed;

	edit_distance_path = my_ed.Alignment();
	std::cout << std::endl << edit_distance_path << std::endl;

	time = clock.getElapsedTime();
	std::cout << "Execution time is: " << time.asSeconds() << " seconds.";
	std::cout << std::endl;







	return 0;
}
