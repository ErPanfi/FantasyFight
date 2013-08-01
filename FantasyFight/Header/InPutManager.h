#ifndef FANTASYFIGHT_INPUTMANAGER_H
#define FANTASYFIGHT_INPUTMANAGER_H

#include "Entity.h"
#include "List.h"


class InputManager
{
public:
	static InputManager& instance ()
	{
		static InputManager istanceIPMan;
		return istanceIPMan;
	}

	~InputManager(){}

	void selectedOnScreen ( Entity::EntityList& listToChoose, Entity* &selectedEntity );

	void pressEnter();

private:

	InputManager(){}
	InputManager(const InputManager& copyIPMan ){}
	InputManager& operator= (const InputManager& copyIPMan ){}

	unsigned int select ( unsigned int maxValue ); //depends on input, range accepted [0 - maxValue]
};

#endif
