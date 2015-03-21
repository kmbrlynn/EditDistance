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
	_s.append("-");
	_t.append("-");

	_m = _s.length();
	_n = _t.length();

	_matrix = new int*[_m];

	for(unsigned int i = 0; i < _m; i++)
	{
		_matrix[i] = new int[_n];
	}
}

ED::~ED()
{
	for(unsigned int i = 0; i < _m; i++)
	{
		delete [] _matrix[i];
	}
	delete _matrix;
}

// ======================================================================= mutators
void ED::BaseCases()
{
	std::string subs, subt;

	for(unsigned int i = _m; i > 0; i--)
	{
		subs = _s.substr(i);
		for(unsigned int j = _n; j > 0; j--)
		{
			subt = _t.substr(j);
		
			// bottom row
			if(i == _m)
				_matrix[i-1][j-1] = ( _n - (_n - subt.length()) ) * INSERT;
			
			// right column
			if(j == _n) 
				_matrix[i-1][j-1] = ( _m - (_m - subs.length()) ) * INSERT;
		}
	}
}

int ED::penalty(char a, char b)
{
	return ((a == b) ?  MATCH : REPLACE); 
}

int ED::min(int& a, int& b, int& c)
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

	for(unsigned int i = _m-1; i > 0; i--)
	{
		for(unsigned int j = _n-1; j > 0; j--)
		{
			// potential values of current square, if you arrived from the...
			int bottom = _matrix[i][j-1] + INSERT;
			int right = _matrix[i-1][j] + INSERT; 
			int diag = _matrix[i][j] + (penalty(_s.at(i-1), _t.at(j-1))); 

			opt_distance = min(bottom, right, diag);
			_matrix[i-1][j-1] = opt_distance;
		}
	}
	return opt_distance;
}

std::string ED::Alignment()
{
	std::string alignment;
	unsigned int i = 0, j = 0;

	int* currentptr = &_matrix[i][j];
	int* rightptr = &_matrix[i][j+1];
	int* diagptr = &_matrix[i+1][j+1];	
	int* bottomptr = &_matrix[i+1][j];

	int* chosenptr;// = currentptr;

	while(i < _m-1 || j < _n-1)
	{
		if(j < _n-1 && (*currentptr - *rightptr) == INSERT)
		{
			alignment.append("-");			// _s would be a gap (x)
			alignment.append(" ");
			alignment.push_back(_t.at(j));	// _t would be a letter (y)
			alignment.append(" ");
			alignment.append("2");
			alignment.append("\n");
			chosenptr = rightptr;
			j++;				
		}

		else if ((*currentptr - *diagptr) == penalty(_s.at(i), _t.at(j)))
		{
			alignment.push_back(_s.at(i)); // _s would be a letter (x)
			alignment.append(" ");
			alignment.push_back(_t.at(j)); // _t would be a letter (y)
			alignment.append(" ");
			if ((*currentptr - *diagptr) == MATCH) 
				alignment.append("0");
			if ((*currentptr - *diagptr) == REPLACE)
				alignment.append("1");
			alignment.append("\n");
			chosenptr = diagptr;
			i++;
			j++;				
		}

		else if(i < _m-1 && (*currentptr - *bottomptr) == INSERT)
		{
			alignment.push_back(_s.at(i));	// _s would be a letter (x)
			alignment.append(" ");
			alignment.append("-"); 			// _t would be a gap (y)
			alignment.append(" ");
			alignment.append("2");
			alignment.append("\n");
			chosenptr = bottomptr;
			i++;				
		}

		// update based on the square (right, diag, bottom) you chose 
		currentptr = chosenptr;
		rightptr = &_matrix[i][j+1];
		diagptr = &_matrix[i+1][j+1];	
		bottomptr = &_matrix[i+1][j];
	} 

	return alignment;
}

// ==================================================================== print matrix
std::ostream& operator <<(std::ostream& os, const ED& ed)
{
	// print _t string across the top (to label the columns) - this is y
	std::cout << "    ";
	for(unsigned int i = 0; i < ed._n; i++)
		std::cout << "    " << ed._t.at(i);
	std::cout << std::endl;

	for(unsigned int i = 0; i < ed._m; i++)
	{
		// print _s string along the side (to label rows) - this is x
		std::cout << std::endl << ed._s.at(i) << "   ";
		for(unsigned int j = 0; j < ed._n; j++)
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

