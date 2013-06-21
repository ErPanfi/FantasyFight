#ifndef FANTASYFIGHT_ENTITY_H
#define FANTASYFIGHT_ENTITY_H

#include "Printable.h"

class Entity
{
public:

	Entity(){};

protected:

	virtual Entity& selectedEntity() const { return *(const_cast<Entity*>(this)); }
	virtual Printable* printEntity(){ return nullptr; }

};

#endif