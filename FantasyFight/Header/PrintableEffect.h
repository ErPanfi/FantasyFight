#ifndef FANTASYFIGHT_PRINTABLEEFFECT_H
#define FANTASYFIGHT_PRINTABLEEFFECT_H

#include "Printable.h"

class PrintableEffect:public Printable
{
private:
	
public:
	PrintableEffect()
	
	{
	}

	virtual MyString toString() const;
};

#endif