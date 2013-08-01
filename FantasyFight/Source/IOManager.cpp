#include "IOManager.h"

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

inline void IOManager::manageOutput(Entity::EntityList& list, bool prefixNumbers)
{
	Entity::EntityList::Iterator iter = list.begin();
	Entity::EntityList::Iterator endIter = list.end();

	unsigned int x = 0;

	for(; iter!= endIter; ++iter)
	{
		Printable* toPrint = (*iter.current()) -> printEntity();
		if(prefixNumbers)
		{
			MyString newOut(++x);
			newOut += " - ";
			newOut += toPrint -> toString();
			toPrint -> setOutputString(newOut);
		}
		manageOutput(toPrint);
	}
}

void IOManager::manageOutput(Printable* toPrint)
{
	OutputRecord* outputRecord = new OutputRecord(toPrint);	//this will be destroyed in flush()

	m_spoolQueue.push_back(outputRecord);
}

void IOManager::manageInput(Entity::EntityList& list, Entity** selection)
{
	//old version: immediate input is no longer required. Use spooler instead.
	/*
	//first output all list
	manageOutput(list, true);
	manageOutput(new Printable(MyString("Make your choice:")));
	OutputManager::instance().sendOnScreen();

	//then ask for the user choice
	InputManager::instance().selectedOnScreen(list, selection);
	*/
	
	//first enqueue the output of all the list content
	manageOutput(MyString("\nMake your choice:"));
	manageOutput(list, true);

	//then enqueue the input request
	InputRecord* inputRecord = new InputRecord(list, *selection);
	m_spoolQueue.push_back(inputRecord);
}

void IOManager::pressEnter()
{
	IOManager::manageOutput(MyString("<Press Enter Key>"));
	m_spoolQueue.push_back(new InputRecord());
}

//flush all the content of the spooler and send them to I/O managers
void IOManager::flush()
{
	for(SpoolQueue::Iterator iter = m_spoolQueue.begin(); iter != m_spoolQueue.end();)
	{
		if(iter.current() -> isOutput)
		{
			OutputRecord* toOut = iter.current() -> data.outputData;
			iter.remove(); //remove element and advance iterator 
			OutputManager::instance().sendOnScreen(toOut -> toPrint);
			delete toOut;
		}
		else
		{
			InputRecord* toIn = iter.current() -> data.inputData;
			iter.remove(); //remove element and advance iterator

			//if a 
			if(toIn -> selection)
				InputManager::instance().selectedOnScreen(toIn -> choices, *toIn -> selection);
			else
				InputManager::instance().pressEnter();
			delete toIn;
		}
	}
}