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

	//spooler moved to IOManager
	/*
	static const unsigned int OTUPUT_SPOOL_SIZE = 255;
	typedef List<Printable*, OTUPUT_SPOOL_SIZE> SpoolList;
	void sendOnScreen ();						//send of screen all the contents of the spool
	void enqueueToSpool(Printable* toSpool);	//enqueue the printable on the spool
	inline bool spoolEmpty() const { return m_spool.empty(); }
	SpoolList m_spool;
	*/
	//void print(Printable* printThis); //cambiato nome in sendOnScreen, per poterlo utilizzare direttamente con i printable
};

#endif