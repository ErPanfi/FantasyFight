#include "InputManager.h"

unsigned int InputManager::select( unsigned int maxValue)
{
	unsigned int temp;
	std::cin>>temp;

	while( temp < 0  || temp > maxValue )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout<<"\nWrong value, please insert a different one: ";
		std::cin>>temp;
	}

	return temp;
}

Entity* InputManager::selectedOnScreen(Entity::EntityList& listToChoose)
{
	unsigned int selected;
	selected = select(listToChoose.size()); //da vedere se la size è corretta luca
	return *listToChoose.selectedElement(selected);

}
