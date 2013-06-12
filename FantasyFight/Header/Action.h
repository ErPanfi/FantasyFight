#ifndef FANTASYFIGHT_ACTION_H
#define FANTASYFIGHT_ACTION_H

#include "Attack.h"

class Character;

class Action
{
private:
	Character* m_owner;

	//attack management
	Attack* m_attack;
	friend void Attack::addAnotherAction(Action* newAction);
	void setAttack(Attack* newValue) { m_attack = newValue; }

public:
	
	Action(Character* owner);

	//attack handling: get only
	Attack* getAttack() const	{ return m_attack; }

};

#endif