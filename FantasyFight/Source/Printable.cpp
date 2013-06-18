#include "Printable.h"

MyString PrintableCharacter::toString() const
{
	MyString ret;
	return ret;
}

MyString PrintableMP::toString() const
{
	MyString tempString ( "Obtaines: ");
	char* tempChar;
	itoa ( m_increment, tempChar,10);
	tempString.append(tempChar);
	tempString.append(" MP\nActual MP: ");
	itoa ( m_nextMP, tempChar, 10);
	tempString.append(tempChar);
    return tempString;
}

MyString PrintableFatigue::toString() const
{
	MyString tempString ( "Increment Fatigue: ");
	char* tempChar;
	itoa ( m_increment, tempChar,10);
	tempString.append(tempChar);
	tempString.append(" \nActual Fatigue: ");
	itoa ( m_nextFatigue, tempChar, 10);
	tempString.append(tempChar);
	return tempString;
}