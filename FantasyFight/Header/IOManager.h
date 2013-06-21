#ifndef FANTASYFIGHT_IOMANAGER_H
#define FANTASYFIGHT_IOMANAGER_H

#include "OutputManager.h"

class IOManager
{
public:
	IOManager& instance ()
	{
		static IOManager istanceOPMan;
		return istanceOPMan;
	}

	~IOManager();

	void manageOutput();
	void manageInput();

private:

	OutputManager* m_OutputManager;
	//TODO inputmanager


	IOManager(){}
	IOManager(const IOManager& copyOPMan ){}
	IOManager& operator= (const IOManager& copyOPMan ) {}

};


#endif
