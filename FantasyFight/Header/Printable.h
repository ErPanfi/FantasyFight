#ifndef FANTASYFIGHT_PRINTABLE_H
#define FANTASYFIGHT_PRINTABLE_H

#include "MyString.h"
#include "List.h"

class  Printable
{
public:
	static const unsigned int PRINT_SIZE = 10;
	typedef List<Printable*, PRINT_SIZE> PrintableList;

	virtual MyString toString() const = 0;
};

#endif
