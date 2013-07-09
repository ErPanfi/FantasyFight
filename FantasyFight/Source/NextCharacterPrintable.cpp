#include "NextCharacterPrintable.h"
#include "Character.h"

NextCharacterPrintable::NextCharacterPrintable(Character* character)
	: m_character(character)
{}

MyString NextCharacterPrintable::toString() const
{
	MyString ret = "It's " + m_character -> getName() + " turn";

	return ret;
}