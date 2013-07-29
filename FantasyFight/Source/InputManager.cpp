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

Entity* InputManager::selectedOnScreen(Entity::EntityList& listToChoose)
{
	unsigned int selected;
	selected = select(listToChoose.size()); //TODO da vedere se la size è corretta luca
	return *listToChoose.selectedElement(selected - 1);

}

void InputManager::pressEnter()
{
	std::cout << "<Press Enter Key>" << std::endl;
	std::getchar();
	std::getchar();
}