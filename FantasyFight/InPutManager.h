#ifndef FANTASYFIGHT_INPUTMANAGER_H
#define FANTASYFIGHT_INPUTMANAGER_H

#include "List.h"
#include "Solution.h"

class InputManager
{
public:
	InputManager& instance ()
	{
		static InputManager istanceIPMan;
		return istanceIPMan;
	}

	~InputManager();

	Solution* selectSolution ( List<Solution*, Solution::SOLUTIONSIZE>& listOfSelection );

private:

	InputManager(){}
	InputManager(const InputManager& copyIPMan ){}
	InputManager& operator= (const InputManager& copyIPMan ){}
};

#endif
