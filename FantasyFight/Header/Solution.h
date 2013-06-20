#ifndef FANTASYFIGHT_SOLUTION_H
#define FANTASYFIGHT_SOLUTION_H

#include "MyString.h"

template <class T, typename Output >
class Solution
{
public:
	static const unsigned int SOLUTIONSIZE = 10;

	Solution()
	{

	}
	Solution(T* inOwner, MyString inDescription)
	{

	}
	
	T* selectedSolution ();
	Output descriptionSolution()
	{
		return description;
	}


private:
	T* owner;
	Output description;
};


#endif