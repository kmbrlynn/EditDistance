#include "ED.hpp"
#include <string>
#include <cstring>
#include <vector>
#include <iostream>

const int MATCH = 0;
const int REPLACE = 1;
const int INSERT = 2;


// ================================================================= con/destructors
ED::ED(std::string s, std::string t) : _s(s), _t(t)
{
	_s.append("-");
	_t.append("-");

	_matrix = new int*[_s.length()];

	for(unsigned int i = 0; i < _s.length(); i++)
	{
		_matrix[i] = new int[_t.length()];
	}

	for(unsigned int i = 0; i < _s.length(); i++)
	{
		for(unsigned int j = 0; j < _t.length(); j++)
			_matrix[i][j] = 0;
	}
}

ED::~ED()
{
	for(unsigned int i = 0; i < _s.length(); i++)
	{
		delete [] _matrix[i];
	}
	delete _matrix;
}

// ======================================================================= accessors
int ED::penalty(char a, char b)
{
	if(a == b) return 0;
	else return 1;
}

int ED::min(int a, int b, int c)
{
	if(b < a)
		return (b < c) ? b : c;
	
	return (a < c) ? a : c;
}

int ED::OptDistance()
{
	int m, n;
	std::string subs, subt;
	int opt_distance = 0;

	for(unsigned int i = _s.length(); i > 0; i--)
	{
		m = i-1;
		subs = _s.substr(i);
		for(unsigned int j = _t.length(); j > 0; j--)
		{
			n = j-1;
			subt = _t.substr(j);
			if(i == _s.length())
				_matrix[m][n] = (_t.length() - (_t.length() - subt.length())) * INSERT;
			
			if(j == _t.length()) 
				_matrix[m][n] = (_s.length() - (_s.length() - subs.length())) * INSERT;
			
		}
	}
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
	// print _t string across the top (to label the columns)
	std::cout << "    ";
	for(unsigned int i = 0; i < ed._t.length(); i++)
		std::cout << ed._t.at(i) << "  ";
	std::cout << std::endl;

	for(unsigned int i = 0; i < ed._s.length(); i++)
	{
		// print _s string along the side (to label rows)
		std::cout << std::endl << ed._s.at(i) << "   ";
		for(unsigned int j = 0; j < ed._t.length(); j++)
		{
			// print contents of squares
			std::cout << ed._matrix[i][j] << "  ";		
		}
	}
	std::cout << std::endl;
	
	return os;
}







