#ifndef FANTASYFIGHT_BRAIN_H
#define FANTASYFIGHT_BRAIN_H


#include "Global.h"

class Action;
class Character;
class Team;

class Brain
{
protected:
	Character* m_owner;

	//friend void Character::setBrainOwner();
	void		setOwner(Character* newOwner)	{ m_owner = newOwner; }

public:

	//ownership management
	Character*	getOwner() const				{ return m_owner; }

	//action deciding
	virtual Action* buildNewActionForOwner() = 0;
	//create a new Character and become its brain
	virtual Character* buildOwner(g_CharacterClassEnum ownerClass) = 0;

	static Brain* buildABrain();
};

#endif