#include <SFML/System.hpp>
#include "ED.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	std::string s; // corresponds to: x, rows of matrix, i indices
	std::string t; // corresponds to: y, columns of matrix, j indices

	std::cin >> s; // first string in file
	std::cin >> t; // second string in file

	int edit_distance;	
	std::string edit_distance_path;

	sf::Clock clock;
	sf::Time time;

	ED my_ed(s,t);

	// lay out a matrix and get the optimal edit distance
	edit_distance = my_ed.OptDistance();

	// recover the path of the optimal edit distance
	edit_distance_path = my_ed.Alignment();

	std::cout << "Edit distance = " << edit_distance << std::endl;
	std::cout << edit_distance_path << std::endl;

	time = clock.getElapsedTime();
	std::cout << "Execution time is: " << time.asSeconds() << " seconds.";
	std::cout << std::endl << std::endl;

	return 0;
}
