#ifndef FANTASYFIGHT_IOMANAGER_H
#define FANTASYFIGHT_IOMANAGER_H

#include "OutPutManager.h"

class IOManager
{
public:
	IOManager& instance ()
	{
		static IOManager istanceOPMan;
		return istanceOPMan;
	}

	~IOManager();

private:

	OutPutManager* m_OutputManager;
	//TODO inputmanager


	IOManager(){}
	IOManager(const IOManager& copyOPMan ){}
	IOManager& operator= (const IOManager& copyOPMan ) {}

};


#endif
