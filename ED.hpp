#include <string>
#include <vector>

class ED
{
public:

	ED(std::string, std::string);
	~ED();

	void BaseCases();
	int penalty(char, char);
	int min(int&, int&, int&);
	int OptDistance();
	std::string Alignment();

	// for debugging
	friend std::ostream& operator <<(std::ostream&, const ED&);

private:

	std::string _s;
	std::string _t;

	unsigned int _m, _n;
	int **_matrix;

};
