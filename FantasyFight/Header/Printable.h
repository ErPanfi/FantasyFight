#ifndef FANTASYFIGHT_PRINTABLE_H
#define FANTASYFIGHT_PRINTABLE_H

#include "MyString.h"
#include "List.h"

class  Printable
{
protected:
	MyString m_outputString;

public:
	static const unsigned int PRINT_SIZE = 10;
	typedef List<Printable*, PRINT_SIZE> PrintableList;

	Printable()
		: m_outputString("")
	{}

	Printable(MyString toOut)
		: m_outputString(toOut)
	{}

	Printable(const char toOut[])
		: m_outputString(toOut)
	{}

	virtual MyString toString() const 
	{
		return m_outputString;
	}
};

#endif
