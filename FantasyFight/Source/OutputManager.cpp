#include "OutputManager.h"
#include <iostream>

using std::cout;
//Spostata la fa�ade nella classe IOManager - EP
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
	cout << toPrint->toString() << std::endl;
	delete toPrint; //da controllare
}

/*
void OutputManager::sendOnScreen()
{
	while(!m_spool.empty())
	{
		SpoolList::Iterator iter = m_spool.begin();
		sendOnScreen(*iter.current());
		iter.remove();
	}
}

void OutputManager::enqueueToSpool(Printable* toSpool)
{
	m_spool.push_back(toSpool);
}
*/