#ifndef FANTASYFIGHT_PRINTABLECHARACTER_H
#define FANTASYFIGHT_PRINTABLECHARACTER_H

#include "Printable.h"

class PrintableCharacter:public Printable
{
private:
	MyString m_name;
	unsigned int m_MP;
	unsigned int m_HP;

public:
	PrintableCharacter( MyString name, unsigned int HP,unsigned int MP);

	virtual MyString toString() const;
};

#endif