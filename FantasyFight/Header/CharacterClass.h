#ifndef FANTASYFIGHT_CHARACTERCLASS_H
#define FANTASYFIGHT_CHARACTERCLASS_H


#include "List.h"
#include "Global.h"

class ActionLibraryRecord;

class CharacterClass
{
public:
	static const unsigned int CHARACTER_CLASS_ACTION_LIST_POOL_SIZE = 20;

private:

	CharacterClass(int attributes[g_AttributesEnum::COUNT_ATTRIB], g_CharacterClassEnum charClass);
	int m_baseAttributes[g_AttributesEnum::COUNT_ATTRIB]; 
	g_CharacterClassEnum m_charClass;

	List<ActionLibraryRecord*,CHARACTER_CLASS_ACTION_LIST_POOL_SIZE> m_classAction;
	static CharacterClass* classLibrary[g_CharacterClassEnum::COUNT_CHARCLASS];

public:

	static CharacterClass* getClassInstance( g_CharacterClassEnum charClass);
	g_CharacterClassEnum getClassEnum() const { return m_charClass; }

};

#endif 