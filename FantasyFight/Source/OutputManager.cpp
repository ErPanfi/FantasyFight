#include "OutputManager.h"
#include <iostream>

using std::cout;
//Spostata la façade nella classe IOManager - EP
/*
void OutputManager::sendOnScreen(Entity &toPrint)
{
	sendOnScreen(toPrint.printEntity());
}

void OutputManager::sendOnScreen ( Entity::EntityList& listToPrint)
{
	Entity::EntityList::Iterator iter = listToPrint.begin();
	Entity::EntityList::Iterator endIter = listToPrint.end();

	for(; iter!= endIter; ++iter)
		sendOnScreen(**iter.current());

}
*/

void OutputManager::sendOnScreen(Printable* toPrint)
{
	cout << toPrint->toString();
	delete toPrint; //da controllare
}