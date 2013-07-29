#include "Character.h"
#include "Action.h"
#include "Brain.h"
#include "ActiveEffect.h"
#include <assert.h>
#include "Game.h"
#include "CharacterClass.h"

#include "PrintableCharacter.h"
#include "IOManager.h"

Character::Character(MyString name, Brain* characterBrain, g_CharacterClassEnum characterClass, g_AttributesEnum attributute_priorities[G_PRIORITIZABLE_ATTRIBS])
	: Targetable(name)
	, m_chargingAction(nullptr)
	, m_brain(characterBrain)
	, m_characterClass(Game::getInstance() -> getClassInstance(characterClass))
	, m_fatigue(0)
	, m_maxMagicPoints(m_characterClass -> getInitialMP())
	, m_maxHealthPoints(m_characterClass -> getInitialHP())
	, m_flags(MASK_EMPTY)
{
	for(int i = 0; i < g_AttributesEnum::COUNT_ATTRIB; ++i)
		m_attributes[i] = m_characterClass -> getAttribute((g_AttributesEnum) i);

	m_attributes[attributute_priorities[0]] += STRONG_ATTRIB_INCREMENT;
	m_attributes[attributute_priorities[1]] += MILD_ATTRIB_INCREMENT;
	m_attributes[attributute_priorities[2]] += WEAK_ATTRIB_INCREMENT;

	m_maxHealthPoints += STR_TO_HP_MULTIPLIER * getAttribModifier(g_AttributesEnum::STR);
	m_maxMagicPoints += INT_TO_MP_MULTIPLIER * getAttribModifier(g_AttributesEnum::INT);

	m_healthPoints = m_maxHealthPoints;
	m_magicPoints = m_maxMagicPoints;
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

unsigned int inline Character::getAttrib(g_AttributesEnum attrib) const
{
	assert(attrib < g_AttributesEnum::COUNT_ATTRIB); //, "Attributes index out of range");
	switch (attrib)
	{
	case DEF:
		return m_attributes[attrib] + getAttribModifier(g_AttributesEnum::DEX);
	default:
		return m_attributes[attrib];
	}
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
	incFatigue(DEFAULT_FATIGUE_INCREMENT - getAttribModifier(g_AttributesEnum::INT)); 
}

bool Character::canActThisTurn() const
{
	//bool ret = true;
	//room for other checks
	//ret &= ...;

	return (m_flags & (MASK_IS_BLOCKED | MASK_IS_DEAD)) == 0;
}

bool inline Character::isDead() const
{
	return (m_flags & MASK_IS_DEAD) != 0;
}

//void Character::setBrainOwner()
//{
//	m_brain -> setOwner(this);
//}

//action management
Action* Character::decideNextAction()
{
	m_chargingAction = m_brain -> buildNewActionForOwner();
	return m_chargingAction;
}

void Character::chargeAction()
{
	m_chargingAction -> chargeUp();	//I'm friend of this class
}

void Character::actionHasBeenResolved()
{
	delete m_chargingAction;

	m_chargingAction = nullptr;
}

//effect management
Character::CharacterActiveEffectsList::Iterator Character::getActiveEffectsIterator() const
{
	return m_activeEffectsList.begin();
}

//with this I'm owner of the effect, and I'm responsible to delete it when it's time
void Character::acquireNewEffect(ActiveEffect* newEffect)
{
	m_activeEffectsList.push_back(newEffect);
	newEffect -> applyAssignmentEffect();
}

void Character::removeActiveEffect(ActiveEffect* targetEffect)
{
	CharacterActiveEffectsList::Iterator iter = m_activeEffectsList.find(&targetEffect);
	if(iter)
	{
		targetEffect -> applyDestructionEffect();
		iter.remove();
		delete targetEffect;	//I'm the owner of this object. I can do wathever I want with this. (╯°□°）╯︵ ┻━┻
	}
}

void Character::receiveDamage(unsigned int damage)
{
	incHP(0 - damage);
	MyString message = m_name + " received " + damage + " damage";
	if(m_healthPoints <= 0)
	{
		message += " and died.";
		m_team -> unregisterCharacter(this);
	}

	IOManager::instance().manageOutput(message);
}

//returning a reference to entity neutralize the const_cast to Character*
/*
Entity& Character::selectedEntity() const
{
	return *(const_cast<Character*>(this)); 
}
*/

Printable* Character::printEntity() const
{
	Printable* temp = new PrintableCharacter(m_name, m_healthPoints,m_magicPoints);
	return temp;
}