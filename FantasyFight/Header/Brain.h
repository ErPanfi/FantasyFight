#ifndef FANTASYFIGHT_BRAIN_H
#define FANTASYFIGHT_BRAIN_H

#include "Character.h"

class Action;

class Brain
{
private:
	Character* m_owner;

	friend void Character::setBrainOwner();

public:

	//ownership management
	Character*	getOwner() const				{ return m_owner; }
	void		setOwner(Character* newOwner)	{ m_owner = newOwner; }

	//action deciding
	virtual Action* buildNewActionForOwner() = 0;
};

#endif