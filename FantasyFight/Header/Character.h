#ifndef FANTASYFIGHT_CHARACTER_H
#define FANTASYFIGHT_CHARACTER_H

#include "ActiveEffect.h"

class Brain;
class Action;

enum g_AttributesEnum
{
	STR = 0,
	DEX,
	INT,
	COUNT_ATTRIB,
};

static const int MIN_ATTRIB_VALUE = 8;

class Character
{
private:

	//attributes
	int m_attributes[g_AttributesEnum::COUNT_ATTRIB];
	int m_fatigue;
	int m_magicPoints;

	//Brain management
	Brain*	m_brain;

	//flags
	unsigned char m_flags;
	static const unsigned char MASK_BLOCKED = 1;

	
public:

	static const int DEFAULT_FATIGUE_INCREMENT = 10;

	//constructor
	Character(Brain* characterBrain);

	//attributes getter & setters
	int inline getAttrib(g_AttributesEnum attrib) const;
	int inline getAttribModifier(g_AttributesEnum attrib) const;
	void inline setAttrib(g_AttributesEnum attrib, int value);

	//status methods
	bool canActThisTurn() const;

	//fatigue getter & setter
	int inline getFatigue() const { return m_fatigue; }
	void inline setFatigue(int newValue) { m_fatigue = newValue; }
	void incFatigue(int offset);
	void incFatigue();
	//function for arbiter heap comparison
	static bool compareFatigue(Character* &lesser, Character* &greater);	

	//MP handling
	int inline getMP() const		{ return m_magicPoints; }
	void inline setMP(int newValue)	{ m_magicPoints = newValue; }
	void inline incMP(int offset)	{ m_magicPoints += offset; }
	void inline incMP()				{ incMP(getAttribModifier(g_AttributesEnum::INT)); }

	//active effects handling
	void acquireNewEffect(ActiveEffect* newEffect);
	ActiveEffect* getActiveEffects() const;

	//brain handling
	Brain* getBrain() const { return m_brain; }
	//can't set the brain, for now
	Action* decideNextAction() const;

	void setBrainOwner();

};

#endif