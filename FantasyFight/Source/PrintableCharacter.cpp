#include "PrintableCharacter.h"

MyString PrintableCharacter::toString() const
{
	return m_name + "\n\t HP: " + m_HP + "\n\t MP: " + m_MP;
}

PrintableCharacter::PrintableCharacter( MyString name, unsigned int HP,unsigned int MP)
		: m_name(name)
		,m_MP(MP)
		,m_HP(HP)
{
}
