#include "Character.h"
#include "Action.h"
#include "Brain.h"
#include <assert.h>

int inline Character::getAttrib(g_AttributesEnum attrib) const
{
	assert(attrib < g_AttributesEnum::COUNT_ATTRIB); //, "Attributes index out of range");
	return m_attributes[attrib];
}

int inline Character::getAttribModifier(g_AttributesEnum attrib) const
{
	return getAttrib(attrib) / 2 - 5;
}

void inline Character::setAttrib(g_AttributesEnum attrib, int value)
{
	assert(attrib < g_AttributesEnum::COUNT_ATTRIB);		//Attributes index out of range
	assert(value >= MIN_ATTRIB_VALUE);	//attribute value is too low
	m_attributes[attrib] = value;
}

bool Character::compareFatigue(Character* &lesser, Character* &greater)
{
	return lesser -> m_fatigue < greater -> m_fatigue || (lesser -> m_fatigue == greater -> m_fatigue && lesser -> getAttrib(g_AttributesEnum::INT) > greater -> getAttrib(g_AttributesEnum::INT));
}

Character::Character(Brain* characterBrain)
	: m_brain(characterBrain)
	, m_fatigue(0)
	, m_flags(0)
{
}

void Character::incFatigue(int offset) 
{ 
	m_fatigue += offset; 
}

void Character::incFatigue() 
{ 
	m_fatigue += (DEFAULT_FATIGUE_INCREMENT - getAttribModifier(g_AttributesEnum::INT)); 
}

bool Character::canActThisTurn() const
{
	return (m_flags | MASK_BLOCKED) != 0;
}

void Character::setBrainOwner()
{
	m_brain -> setOwner(this);
}

Action* Character::decideNextAction() const
{
	//TODO implement
	return nullptr;
}