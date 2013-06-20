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
	_itoa_s ( m_increment, tempChar,10);
	tempString.append(tempChar);
	tempString.append(" MP\nActual MP: ");
	_itoa_s ( m_nextMP, tempChar, 10);
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
	_itoa_s ( m_increment, tempChar,10);
	tempString.append(tempChar);
	tempString.append(" \nActual Fatigue: ");
	_itoa_s ( m_nextFatigue, tempChar, 10);
	tempString.append(tempChar);
	return tempString;
}

MyString PrintableAction::toString() const
{
	MyString ret;
	return ret;
}

