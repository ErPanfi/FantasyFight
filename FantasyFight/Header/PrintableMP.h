#ifndef FANTASYFIGHT_PRINTABLEMP_H
#define FANTASYFIGHT_PRINTABLEMP_H

#include "Printable.h"

class PrintableMP:public Printable
{
private:
	int m_increment;
	unsigned int m_nextMP;
public:
	PrintableMP(unsigned int MP, int offsetMP);

	virtual MyString toString() const;
};

#endif