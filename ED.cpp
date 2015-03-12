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
	int current, diag, right, bottom;
	std::vector<int> neighbors;

	while(i <= _s.length()-1 || j <= _t.length()-1)
	{
		current = _matrix[i][j];
		diag = _matrix[i+1][j+1];
		right = _matrix[i][j+1];
		bottom = _matrix[i+1][j];
		neighbors.push_back(diag);
		neighbors.push_back(right);
		neighbors.push_back(bottom);
		
		// sort the 3 neighbors, determine smallest
		std::sort(neighbors.begin(), neighbors.end());
		int smallest = neighbors[0];

		// between smallest and current
		int cost;
		int difference = current - smallest;

		if(&smallest == &diag)
		{
			cost = (penalty(_s.at(i), _t.at(j)));

			// if it's legal for path to have gone this way	
			if (difference == cost)
			{
				alignment.push_back(_s.at(i+1));
				alignment.append(" ");
				alignment.push_back(_t.at(j+1));
				alignment.append(" ");
				if (cost == MATCH)
					alignment.push_back(MATCH);
				if (cost == REPLACE)
					alignment.push_back(REPLACE);
				alignment.append(" \n");
				i++;
				j++;				
			}
			// otherwise, path must have gone thru next-smallest
			else smallest = neighbors[1];
		}

		if(&smallest == &right)
		{
			cost = INSERT;
			
			// if it's legal for path to have gone this way	
			if (difference == cost)
			{
				alignment.push_back(_s.at(i));
				alignment.append(" ");
				alignment.append("-"); // instead of j+1
				alignment.append(" ");
				alignment.push_back(INSERT);
				alignment.append(" \n");
				j++;				
			}
			// otherwise, path must have gone thru next-smallest
			else smallest = neighbors[1];
		}

		if(&smallest == &bottom)
		{
			cost = INSERT;
			
			// if it's legal for path to have gone this way	
			if (difference == cost)
			{
				alignment.append("-"); // instead of i+1
				alignment.append(" ");
				alignment.push_back(_t.at(j));
				alignment.append(" ");
				alignment.push_back(INSERT);
				alignment.append(" \n");
				i++;				
			}
			// otherwise, path must have gone thru next-smallest
			else smallest = neighbors[1];
			
		}
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







