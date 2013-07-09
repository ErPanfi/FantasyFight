#ifndef FANTASYFIGHT_IOMANAGER_H
#define FANTASYFIGHT_IOMANAGER_H

#include "OutputManager.h"
#include "InputManager.h"

class IOManager
{
public:
	static IOManager& instance ()
	{
		static IOManager istanceOPMan;
		return istanceOPMan;
	}

	~IOManager();

	void manageOutput(Entity::EntityList& list);
	void manageOutput(Entity& entity);
	void manageOutput(Printable* toPrint);

	Entity* manageInput(Entity::EntityList& list);

private:

	//TODO inputmanager

	IOManager();
	IOManager(const IOManager& copyOPMan );
	IOManager& operator= (const IOManager& copyOPMan );

	void unInit();
	void initFromOther(const IOManager& other);

};


#endif
