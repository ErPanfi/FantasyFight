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

void IOManager::manageOutput(Entity::EntityList& list, bool prefixNumbers)
{
	OutputManager *outManager = &(OutputManager::instance());

	Entity::EntityList::Iterator iter = list.begin();
	Entity::EntityList::Iterator endIter = list.end();

	unsigned int x = 0;

	for(; iter!= endIter; ++iter)
	{
		if(prefixNumbers)
			std::cout << ++x << " - ";
		outManager -> sendOnScreen((*iter.current()) -> printEntity());
	}
}

void IOManager::manageOutput(Entity& entity)
{
	OutputManager::instance().sendOnScreen(entity.printEntity());
}

void IOManager::manageOutput(Printable* toPrint)
{
	OutputManager::instance().sendOnScreen(toPrint);
}

void IOManager::manageOutput(MyString &string)
{
	OutputManager::instance().sendOnScreen(new Printable(string));
}

Entity* IOManager::manageInput(Entity::EntityList& list)
{
	manageOutput(list, true);
	manageOutput(new Printable(MyString("Make a choice:")));
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