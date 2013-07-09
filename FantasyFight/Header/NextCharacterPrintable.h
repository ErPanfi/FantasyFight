#ifndef FANTASYFIGHT_NEXTCHARACTERPRINTABLE_H
#define FANTASYFIGHT_NEXTCHARACTERPRINTABLE_H

#include "Printable.h"

class Character;

class NextCharacterPrintable : public Printable
{
private:
	Character*	m_character;
public:
	NextCharacterPrintable(Character* character);

	virtual MyString toString() const;
};

#endif