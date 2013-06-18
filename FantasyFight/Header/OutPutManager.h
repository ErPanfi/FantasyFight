#ifndef FANTASYFIGHT_OUTPUTMANAGER_H
#define FANTASYFIGHT_OUTPUTMANAGER_H

#include "Printable.h"
#include "List.h"

class OutPutManager
{
public:
	OutPutManager& instance ()
	{
		static OutPutManager istanceOPMan;
		return istanceOPMan;
	}

	~OutPutManager();

	void printList ( List<Printable*,Printable::PRINTSIZE>& listToPrint );

private:

	OutPutManager(){}
	OutPutManager(const OutPutManager& copyOPMan ){}
	OutPutManager& operator= (const OutPutManager& copyOPMan ){}

};

#endif