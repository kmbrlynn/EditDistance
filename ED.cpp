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
}

ED::~ED()
{
	for(unsigned int i = 0; i < _s.length(); i++)
	{
		delete [] _matrix[i];
	}
	delete _matrix;
}

// ======================================================================= mutators
void ED::BaseCases()
{
	std::string subs, subt;

	for(unsigned int i = _s.length(); i > 0; i--)
	{
		subs = _s.substr(i);
		for(unsigned int j = _t.length(); j > 0; j--)
		{
			subt = _t.substr(j);
		
			// bottom row
			if(i == _s.length())
				_matrix[i-1][j-1] = (_t.length() - (_t.length() - subt.length())) * INSERT;
			
			// right column
			if(j == _t.length()) 
				_matrix[i-1][j-1] = (_s.length() - (_s.length() - subs.length())) * INSERT;
		}
	}
}

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
	int opt_distance;

	// first go through and fill out bottom row / right column
	BaseCases();

	for(unsigned int i = _s.length()-1; i > 0; i--)
	{
		for(unsigned int j = _t.length()-1; j > 0; j--)
		{
			// potential values of current square, if you arrived from the...
			int bottom = _matrix[i][j-1] + INSERT;
		//	std::cout << bottom << ", ";
			int right = _matrix[i-1][j] + INSERT; 
		//	std::cout << right << ", ";
			int diag = _matrix[i][j] + ((_s.at(i-1) == _t.at(j-1)) ?  MATCH : REPLACE); 
		//	std::cout << diag << " = ";

			opt_distance = min(bottom, right, diag);
		//	std::cout << "opt " << opt_distance << " | ";
			_matrix[i-1][j-1] = opt_distance;
		}
	//	std::cout << std::endl;
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
		std::cout << "    " << ed._t.at(i);
	std::cout << std::endl;

	for(unsigned int i = 0; i < ed._s.length(); i++)
	{
		// print _s string along the side (to label rows)
		std::cout << std::endl << ed._s.at(i) << "   ";
		for(unsigned int j = 0; j < ed._t.length(); j++)
		{
			// print contents of squares
			if(ed._matrix[i][j] > 9)
				std::cout << "   " << ed._matrix[i][j];
			else
				std::cout << "    " << ed._matrix[i][j];		
		}
	}
	std::cout << std::endl;
	
	return os;
}







