#ifndef FANTASYFIGHT_BRAIN_H
#define FANTASYFIGHT_BRAIN_H


#include "Global.h"

class Action;
class Character;
class Team;
class ActionLibraryRecord;
class Targetable;

class Brain
{
protected:
	Character* m_owner;

	//friend void Character::setBrainOwner();
	void		setOwner(Character* newOwner)	{ m_owner = newOwner; }

	virtual ActionLibraryRecord* decideAction(Targetable* target = nullptr) = 0;
	virtual Targetable* decideTarget(ActionLibraryRecord* actionRecord = nullptr) = 0;

public:

	//ownership management
	Character*	getOwner() const				{ return m_owner; }

	//action deciding
	virtual Action* buildNewActionForOwner();
	//create a new Character and become its brain
	virtual Character* buildOwner(g_CharacterClassEnum ownerClass) = 0;

	static Brain* buildABrain(bool humanBrain);
};

#endif