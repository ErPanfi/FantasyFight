#ifndef FANTASYFIGHT_CHARACTERCLASS_H
#define FANTASYFIGHT_CHARACTERCLASS_H


#include "List.h"
#include "Global.h"

class ActionLibraryRecord;

class CharacterClass
{
public:
	static const unsigned int CHARACTER_CLASS_ACTION_LIST_POOL_SIZE = 20;
	
	typedef unsigned char CharacterClassBitmask;
	static const CharacterClassBitmask ALL_CLASSES_BITMASK	=	1 << g_CharacterClassEnum::THIEF	//all classes can perform this
															|	1 << g_CharacterClassEnum::WARRIOR
															|	1 << g_CharacterClassEnum::WIZARD;

	static g_CharacterClassEnum randomClass();

private:

	CharacterClass(unsigned int attributes[g_AttributesEnum::COUNT_ATTRIB], g_CharacterClassEnum charClass, unsigned int hp, unsigned int mp);
	friend class Game;
	unsigned int m_baseAttributes[g_AttributesEnum::COUNT_ATTRIB]; 
	unsigned int m_initialHP;
	unsigned int m_initialMP;
	g_CharacterClassEnum m_charClass;
	//List<ActionLibraryRecord*,CHARACTER_CLASS_ACTION_LIST_POOL_SIZE> m_classAction; TODO remove

public:
	//members getters
	unsigned int getAttribute(g_AttributesEnum attrib) const { return m_baseAttributes[attrib]; }
	unsigned int getInitialHP() const { return m_initialHP; }
	unsigned int getInitialMP() const { return m_initialMP; }
	g_CharacterClassEnum getClassEnum() const { return m_charClass; }

};

#endif 