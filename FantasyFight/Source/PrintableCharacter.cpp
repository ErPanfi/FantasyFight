#include "PrintableCharacter.h"

MyString PrintableCharacter::toString() const
{
	MyString tempString ("\n");
	tempString.append(m_name);
	tempString.append("\n\t HP: ");
	char tempchar[3];
	_itoa_s( m_HP,tempchar,10);
	tempString.append(tempchar);
	tempString.append("\n\t MP: ");
	_itoa_s( m_MP,tempchar,10);
	return tempString;
}

PrintableCharacter::PrintableCharacter( MyString name, unsigned int HP,unsigned int MP)
		: m_name(name)
		,m_MP(MP)
		,m_HP(HP)
{
}
