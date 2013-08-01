#include "PrintableMP.h"

MyString PrintableMP::toString() const
{
    return MyString("Obtaines ") + m_increment + " MP, reaching " + m_nextMP + " MP.\n";
}

PrintableMP::PrintableMP(unsigned int MP, int offsetMP)
	: m_increment(offsetMP)
	, m_nextMP(MP)
{
}