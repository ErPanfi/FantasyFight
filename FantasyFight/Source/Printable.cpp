#include "Printable.h"

MyString PrintableMP::toString() const
{
	MyString tempString ( "Obtaines ");
	char* tempChar;
	itoa ( m_increment, tempChar,10);
	tempString.append(tempChar);
	tempString.append("\nActual MP: ");
	itoa ( m_nextMP, tempChar, 10);
	tempString.append(tempChar);
    return tempString;
}