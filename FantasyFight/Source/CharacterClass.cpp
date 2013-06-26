#include "CharacterClass.h"

#include "Game.h"
#include "Arbiter.h"

CharacterClass::CharacterClass(unsigned int attributes[g_AttributesEnum::COUNT_ATTRIB], g_CharacterClassEnum charClass, unsigned int hp, unsigned int mp)
	: m_charClass(charClass)
	, m_initialHP(hp)
	, m_initialMP(mp)
{
	for(int i = 0; i < g_AttributesEnum::COUNT_ATTRIB; ++i)
		m_baseAttributes[i] = attributes[i];
}

g_CharacterClassEnum CharacterClass::randomClass()
{
	return (g_CharacterClassEnum) (Game::getInstance() -> getArbiter() -> randomNumber(0, g_CharacterClassEnum::COUNT_CHARCLASS - 1));
}