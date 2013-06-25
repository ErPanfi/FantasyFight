#include "OutPutManager.h"
#include <iostream>

using std::cout;

void OutputManager::sendOnScreen(Entity &toPrint)
{
	printer(toPrint.printEntity());
}

void OutputManager::sendOnScreen ( Entity::EntityList& listToPrint)
{
	Entity::EntityList::Iterator iter = listToPrint.begin();
	Entity::EntityList::Iterator endIter = listToPrint.end();

	for(; iter!= endIter; ++iter)
		sendOnScreen(**iter.current());

}

void OutputManager::printer(Printable* printThis)
{
	cout << printThis->toString();
	delete printThis; //da controllare
}
