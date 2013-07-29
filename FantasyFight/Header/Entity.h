#ifndef FANTASYFIGHT_ENTITY_H
#define FANTASYFIGHT_ENTITY_H

#include "Printable.h"

class Entity
{
protected:
	MyString m_name;

public:

	Entity(MyString name)
		: m_name(name)
	{}

	static const unsigned int ENTITY_SIZE = 10;
	typedef List<Entity*, ENTITY_SIZE> EntityList;

	virtual Entity& selectedEntity()	const { return *(const_cast<Entity*>(this)); }
	virtual Printable* printEntity()	const { return new Printable(m_name); }
	inline	MyString getName()			const { return m_name; }

};

#endif