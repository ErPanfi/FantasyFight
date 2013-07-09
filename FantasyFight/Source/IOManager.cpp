#include "IOManager.h"

//Da notare come questi metodi incapsulino solo una singola chiamata ad un altro metodo... Alziamo di un livello la façade, valà =]
/*
void IOManager::manageOutput(Entity::EntityList& list)
{
	OutputManager::instance().sendOnScreen(list);
}

void IOManager::manageOutput(Entity& entity)
{
	OutputManager::instance().sendOnScreen(entity);
}
*/

void IOManager::manageOutput(Entity::EntityList& list)
{
	OutputManager *outManager = &(OutputManager::instance());

	Entity::EntityList::Iterator iter = list.begin();
	Entity::EntityList::Iterator endIter = list.end();

	for(; iter!= endIter; ++iter)
		outManager -> sendOnScreen((*iter.current()) -> printEntity());
}

void IOManager::manageOutput(Entity& entity)
{
	OutputManager::instance().sendOnScreen(entity.printEntity());
}

void IOManager::manageOutput(Printable* toPrint)
{
	OutputManager::instance().sendOnScreen(toPrint);
}

Entity* IOManager::manageInput(Entity::EntityList& list)
{
	manageOutput(list);
	return InputManager::instance().selectedOnScreen(list);
}

//ctors, dtor and assignment
//acculy these do nothing

void IOManager::unInit() {}			

void IOManager::initFromOther(const IOManager& other) {}

IOManager::~IOManager()
{
	unInit();
}

IOManager::IOManager() {}

IOManager::IOManager(const IOManager& copyOPMan)
{
	initFromOther(copyOPMan);
}

IOManager& IOManager::operator=(const IOManager& copyOPMan)
{
	if(this != & copyOPMan)
	{
		unInit();
		initFromOther(copyOPMan);
	}

	return *this;
}