#ifndef FANTASYFIGHT_CHARACTER_H
#define FANTASYFIGHT_CHARACTER_H

#include "ActiveEffect.h"
#include "Brain.h"

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

	Brain*	brain;

public:

	static const int DEFAULT_FATIGUE_INCREMENT = 10;

	//constructor
	Character(Brain* characterBrain);

	//attributes getter & setters
	int inline getAttrib(g_AttributesEnum attrib) const;
	int inline getAttribModifier(g_AttributesEnum attrib) const;
	void inline setAttrib(g_AttributesEnum attrib, int value);

	//fatigue getter & setter
	int inline getFatigue() const { return m_fatigue; }
	void inline setFatigue(int newValue) { m_fatigue = newValue; }
	void inline incFatigue(int offset) { m_fatigue += offset; }
	void inline incFatigue() { incFatigue(DEFAULT_FATIGUE_INCREMENT - getAttribModifier(g_AttributesEnum::INT)); }
	//function for arbiter heap comparison
	static bool compareFatigue(Character* &lesser, Character* &greater);	

	//MP handling
	int getMP() const			{ return m_magicPoints; }
	void setMP(int newValue)	{ m_magicPoints = newValue; }
	void incMP(int offset)		{ m_magicPoints += offset; }
	void incMP()				{ incMP(getAttribModifier(g_AttributesEnum::INT)); }

	//active effects handling
	void acquireNewEffect(ActiveEffect* newEffect);
	ActiveEffect* getActiveEffects() const;

	//brain handling
};

#endif