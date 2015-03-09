#include "ED.hpp"
#include <string>
#include <vector>
#include <iostream>

const int MATCH = 0;
const int REPLACE = 1;
const int INSERT = 2;


// ================================================================= con/destructors
ED::ED(std::string s, std::string t) : _s(s), _t(t)
{
	_slen = _s.size();
	_tlen = _t.size();

	_matrix = new int*[_slen];
	for(int i = 0; i < _slen; i++)
	{
		_matrix[i] = new int[_tlen];
	}

	for(int i = 0; i < _slen; i++)
	{
		for(int j = 0; j < _tlen; j++)
			_matrix[i][j] = 0;
	}
}

ED::~ED()
{
	for(int i = 0; i < _slen; i++)
	{
		delete [] _matrix[i];
	}
	delete _matrix;
}

// ======================================================================= accessors
int ED::penalty(char a, char b)
{
	int penalty = 0;

	return penalty;
}

int ED::min(int a, int b, int c)
{
	int min = 0;

	return min;
}

int ED::OptDistance()
{
	int opt_distance = 0;

	return opt_distance;
	
}

std::string ED::Alignment()
{
	std::string alignment;

	return alignment;
}

// ==================================================================== print matrix
std::ostream& operator <<(std::ostream& os, const ED& ed)
{
	for(int i = 0; i < ed._slen; i++)
	{
		for(int j = 0; j < ed._tlen; j++)
		{
			std::cout << ed._matrix[i][j] << "  ";		
		}
		std::cout << std::endl;
	}

	return os;
}







