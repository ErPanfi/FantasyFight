#include "PrintableFatigue.h"

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