#include "ED.hpp"
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

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

	for(unsigned int i = _s.length()-1; i > 0; i--)
	{
		for(unsigned int j = _t.length()-1; j > 0; j--)
		{
			// potential values of current square, if you arrived from the...
			int bottom = _matrix[i][j-1] + INSERT;
		//	std::cout << bottom << ", ";
			int right = _matrix[i-1][j] + INSERT; 
		//	std::cout << right << ", ";
			int diag = _matrix[i][j] + (penalty(_s.at(i-1), _t.at(j-1))); 
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
	unsigned int i = 0, j = 0;

	int* currentptr = &_matrix[i][j];
	int* rightptr = &_matrix[i][j+1];
	int* diagptr = &_matrix[i+1][j+1];	
	int* bottomptr = &_matrix[i+1][j];

	while(i < _s.length()-1 || j < _t.length()-1)
	{
//		std::cout << "i = " << i << " | j = " << j << "\n";
		int* neighbors[] = {rightptr, diagptr, bottomptr};
		int* chosenptr;

		// try each neighboring square
		for(int k = 0; k < 3; k++)
		{
			// ================================================ if neighbor is Right
			if(neighbors[k] == rightptr)
			{
				// and it's legal for the path to have come from there
				if ((*currentptr - *rightptr) == INSERT)
				{
					alignment.append("-");			// _s would be a gap (x)
					alignment.append(" ");
					alignment.push_back(_t.at(j)); // _t would be a letter (y)
					alignment.append(" ");
					alignment.append("2");
					alignment.append(" \n");
					chosenptr = rightptr;
					j++;				
				}
			}
			// choose the right square, move on
			if (chosenptr == rightptr) break;

			// ================================================= if neighbor is Diag
			if(neighbors[k] == diagptr)
			{
				// and it's legal for the path to have come from there
				if ((*currentptr - *diagptr) == penalty(_s.at(i), _t.at(j)))
				{
					alignment.push_back(_s.at(i)); // _s would be a letter (x)
					alignment.append(" ");
					alignment.push_back(_t.at(j)); // _t would be a letter (y)
					alignment.append(" ");
					if ((*currentptr - *diagptr) == MATCH) 
						alignment.append("0");
					if ((*currentptr - *diagptr) == REPLACE)
						alignment.append("1");
					alignment.append(" \n");
					chosenptr = diagptr;
					i++;
					j++;				
				}
			}
			// choose the diagonal square, move on
			if (chosenptr == diagptr) break;
	
			// ================================================ if neighbor is Bottom
			if(neighbors[k] == bottomptr)
			{
				// and it's legal for the path to have come from there
				if ((*currentptr - *bottomptr) == INSERT)
				{
					alignment.push_back(_s.at(i));	// _s would be a letter (x)
					alignment.append(" ");
					alignment.append("-"); 			 	// _t would be a gap (y)
					alignment.append(" ");
					alignment.append("2");
					alignment.append(" \n");
					chosenptr = bottomptr;
					i++;				
				}
			}
			// choose the bottom square, move on
			if (chosenptr == bottomptr) break;
		}

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







