#include <string>
#include <vector>

class ED
{
public:

	ED(std::string, std::string);
	~ED();

	// for debugging
	friend std::ostream& operator <<(std::ostream&, const ED&);

private:

	int penalty(char, char);
	int min(int, int, int);
	int OptDistance();
	std::string Alignment();

	std::string _s;
	std::string _t;

	int _slen;
	int _tlen;

	int **_matrix;
};
