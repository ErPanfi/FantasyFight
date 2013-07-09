#ifndef FANTASYFIGHT_OUTPUTMANAGER_H
#define FANTASYFIGHT_OUTPUTMANAGER_H

#include "Entity.h"
#include "List.h"

class OutputManager
{
public:
	static OutputManager& instance ()
	{
		static OutputManager istanceOPMan;
		return istanceOPMan;
	}

	~OutputManager(){}

	//Spostata la façade nella classe IOManager - EP
	/*
	void sendOnScreen ( Entity::EntityList& listToPrint);
	void sendOnScreen ( Entity& toPrint);
	*/

	void sendOnScreen ( Printable* toPrint);
	
private:

	OutputManager(){}
	OutputManager(const OutputManager& copyOPMan ){}
	OutputManager& operator= (const OutputManager& copyOPMan ){}

	//void print(Printable* printThis); //cambiato nome in sendOnScreen, per poterlo utilizzare direttamente con i printable
};

#endif