#include "PrintableMP.h"

MyString PrintableMP::toString() const
{
	MyString tempString ( "Obtaines ");
	char tempChar[3];
	_itoa_s ( m_increment, tempChar,10);
	tempString.append(tempChar);
	tempString.append(" MP, reaching ");
	_itoa_s ( m_nextMP, tempChar, 10);
	tempString.append(tempChar);
	tempString.append("MP.\n");
    return tempString;
}

PrintableMP::PrintableMP(unsigned int MP, int offsetMP)
	: m_increment(offsetMP)
	, m_nextMP(MP)
{
}