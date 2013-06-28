#include "PrintableMP.h"

MyString PrintableMP::toString() const
{
	MyString tempString ( "\nObtaines: ");
	char tempChar[3];
	_itoa_s ( m_increment, tempChar,10);
	tempString.append(tempChar);
	tempString.append(" MP\nActual MP: ");
	_itoa_s ( m_nextMP, tempChar, 10);
	tempString.append(tempChar);
    return tempString;
}

PrintableMP::PrintableMP(unsigned int MP, int offsetMP)
	: m_increment(offsetMP)
	, m_nextMP(MP)
{
}