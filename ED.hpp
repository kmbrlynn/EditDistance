#include <string>

class ED
{
public:

	ED(std::string, std::string);

private:

	int penalty(char, char);
	int min(int, int, int);
	int OptDistance();
	std::string Alignment();

	std::string _s;
	std::string _t;

};
