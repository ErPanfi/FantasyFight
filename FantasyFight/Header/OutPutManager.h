#ifndef FANTASYFIGHT_OUTPUTMANAGER_H
#define FANTASYFIGHT_OUTPUTMANAGER_H

#include "Entity.h"
#include "List.h"

class OutputManager
{
public:
	OutputManager& instance ()
	{
		static OutputManager istanceOPMan;
		return istanceOPMan;
	}

	~OutputManager();

	void sendOnScreen ( Entity::EntityList& listToPrint);
	void sendOnScreen ( Entity& toPrint);
	
private:

	OutputManager(){}
	OutputManager(const OutputManager& copyOPMan ){}
	OutputManager& operator= (const OutputManager& copyOPMan ){}

	void printer(Printable* printThis); //dipende dall'output
};

#endif