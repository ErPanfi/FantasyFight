#include "CharacterClass.h"

CharacterClass::CharacterClass(int attributes[g_AttributesEnum::COUNT_ATTRIB], g_CharacterClassEnum charClass)
	: m_charClass(charClass)
{
	for(int i = 0; i < g_AttributesEnum::COUNT_ATTRIB; ++i)
		m_baseAttributes[i] = attributes[i];

}