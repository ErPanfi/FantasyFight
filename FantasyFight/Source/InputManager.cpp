#include "InputManager.h"

unsigned int InputManager::select( unsigned int maxValue)
{
	unsigned int temp;
	std::cin>>temp;

	while( temp <= 0  || temp > maxValue )
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout<<"\nWrong value, please insert a different one: ";
		std::cin>>temp;
		std::getchar();		//capture return key
		std::getchar();		//capture return key
	}


	return temp;
}

void InputManager::selectedOnScreen(Entity::EntityList& listToChoose, Entity* &selectedEntity)
{
	unsigned int selected;
	selected = select(listToChoose.size()); //TODO da vedere se la size è corretta luca
	selectedEntity = *listToChoose.selectedElement(selected - 1);

}

void InputManager::pressEnter()
{
	std::getchar();
	std::getchar();
}