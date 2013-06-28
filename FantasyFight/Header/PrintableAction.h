#ifndef FANTASYFIGHT_PRINTABLEACTION_H
#define FANTASYFIGHT_PRINTABLEACTION_H

#include "Printable.h"

class PrintableAction:public Printable
{
public:
	virtual MyString toString() const;
};

#endif