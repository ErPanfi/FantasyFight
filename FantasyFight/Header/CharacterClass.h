#ifndef FANTASYFIGHT_CHARACTERCLASS_H
#define FANTASYFIGHT_CHARACTERCLASS_H


#include "List.h"
#include "Action.h"
#include "Global.h"


class CharacterClass
{
public:

	static const unsigned int CHARACTER_CLASS_ACTION_LIST_POOL_SIZE = 20;
	static CharacterClass* getClassInstance( g_CharacterClassEnum charClass);

private:

	CharacterClass(int attributes[g_AttributesEnum::COUNT_ATTRIB], g_CharacterClassEnum charClass);
	int m_baseAttributes[COUNT_ATTRIB]; 
	g_CharacterClassEnum m_charClass;
	List<Action*,CHARACTER_CLASS_ACTION_LIST_POOL_SIZE> m_classAction;

	static CharacterClass* classLibrary[g_CharacterClassEnum::COUNT_CHARCLASS];
};

#endif 