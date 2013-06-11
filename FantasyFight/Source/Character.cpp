#include "Character.h"
#include <assert.h>

int inline Character::getAttrib(AttributesEnum attrib) const
{
	assert(attrib < AttributesEnum::COUNT); //, "Attributes index out of range");
	return m_attributes[attrib];
}

int inline Character::getAttribModifier(AttributesEnum attrib) const
{
	return getAttrib(attrib) / 2 - 5;
}

void inline Character::setAttrib(AttributesEnum attrib, int value)
{
	assert(attrib < AttributesEnum::COUNT); //, "Attributes index out of range");
	assert(value >= MIN_ATTRIB_VALUE);	//attribute value is too low
	m_attributes[attrib] = value;
}

bool inline Character::compareFatigue(const Character& lesser, const Character& greater)
{
	return lesser.m_fatigue < greater.m_fatigue || (lesser.m_fatigue == greater.m_fatigue && lesser.getAttrib(AttributesEnum::INT) > greater.getAttrib(AttributesEnum::INT));
}