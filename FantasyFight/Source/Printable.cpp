#include "Printable.h"

MyString PrintableCharacter::toString() const
{
	MyString ret;
	return ret;
}

MyString PrintableMP::toString() const
{
	MyString tempString ( "Obtaines: ");
	char tempChar[10];
	itoa ( m_increment, tempChar,10);
	tempString.append(tempChar);
	tempString.append(" MP\nActual MP: ");
	itoa ( m_nextMP, tempChar, 10);
	tempString.append(tempChar);
    return tempString;
}

MyString PrintableEffect::toString() const
{
	MyString ret;
	return ret;
}

MyString PrintableFatigue::toString() const
{
	MyString tempString ( "Increment Fatigue: ");
	char tempChar[10];
	itoa ( m_increment, tempChar,10);
	tempString.append(tempChar);
	tempString.append(" \nActual Fatigue: ");
	itoa ( m_nextFatigue, tempChar, 10);
	tempString.append(tempChar);
	return tempString;
}

MyString PrintableAction::toString() const
{
	MyString ret;
	return ret;
}

