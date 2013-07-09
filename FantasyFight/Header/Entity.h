#ifndef FANTASYFIGHT_ENTITY_H
#define FANTASYFIGHT_ENTITY_H

#include "Printable.h"

class Entity
{
public:

	static const unsigned int ENTITY_SIZE = 10;
	typedef List<Entity*, ENTITY_SIZE> EntityList;

	virtual Entity& selectedEntity() const { return *(const_cast<Entity*>(this)); }
	virtual Printable* printEntity() const { return nullptr; }

};

#endif