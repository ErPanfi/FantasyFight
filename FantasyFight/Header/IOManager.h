#ifndef FANTASYFIGHT_IOMANAGER_H
#define FANTASYFIGHT_IOMANAGER_H

#include "OutputManager.h"
#include "InPutManager.h"

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
	Entity* manageInput(Entity::EntityList& list);

private:

	OutputManager* m_OutputManager;
	//TODO inputmanager


	IOManager(){}
	IOManager(const IOManager& copyOPMan ){}
	IOManager& operator= (const IOManager& copyOPMan ) {}

};


#endif
