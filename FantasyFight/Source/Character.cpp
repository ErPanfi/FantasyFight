#include "Character.h"
#include "Action.h"
#include "Brain.h"
#include "ActiveEffect.h"
#include <assert.h>

Character::Character(Brain* characterBrain)
	: m_brain(characterBrain)
	, m_fatigue(0)
	, m_flags(0)
{
}

void Character::unInit()
{
	//active effects are owned by the character
	for(CharacterActiveEffectsList::Iterator remainingActiveEffects = m_activeEffectsList.begin(); remainingActiveEffects != m_activeEffectsList.end(); ++remainingActiveEffects)
		delete *(remainingActiveEffects.current());
}

void Character::initFromOtherCharacter(const Character& other)
{
	//duplicate active effects
	for(CharacterActiveEffectsList::Iterator remainingActiveEffects = other.m_activeEffectsList.begin(); remainingActiveEffects != other.m_activeEffectsList.end(); ++remainingActiveEffects)		
	{
		ActiveEffect* currActiveEffect = *(remainingActiveEffects.current());
		m_activeEffectsList.push_back(currActiveEffect -> makeCopyOfThis());	//insert in list the pointer to a current effect copy
	}
}

Character::~Character()
{
	unInit();
}

Character& Character::operator=(const Character& other)
{
	if(this != &other)
	{
		unInit();
		initFromOtherCharacter(other);
	}

	return *this;
}

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

Character::CharacterActiveEffectsList::Iterator Character::getActiveEffectsIterator() const
{
	return m_activeEffectsList.begin();
}
