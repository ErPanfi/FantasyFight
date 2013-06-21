#ifndef FANTASYFIGHT_OUTPUTMANAGER_H
#define FANTASYFIGHT_OUTPUTMANAGER_H

#include "Solution.h"
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

	void sendOnScreen ( List<Solution*>& listToPrint);
	void sendOnScreen ( Solution& listToPrint);
	/*void printList ( List<Printable*,Printable::PRINTSIZE>& listToPrint );*/

private:

	OutputManager(){}
	OutputManager(const OutputManager& copyOPMan ){}
	OutputManager& operator= (const OutputManager& copyOPMan ){}

	void printer();
};

#endif