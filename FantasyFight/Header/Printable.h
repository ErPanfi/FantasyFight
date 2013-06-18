#ifndef FANTASYFIGHT_PRINTABLE_H
#define FANTASYFIGHT_PRINTABLE_H

#include "MyString.h"

class  Printable
{
public:
	static const unsigned int PRINTSIZE = 10;
	virtual MyString toString() const = 0;

private:


};

class PrintableCharacter:public Printable
{
public:

	virtual MyString toString() const{};
};

class PrintableMP:public Printable
{
private:
	int m_increment;
	unsigned int m_nextMP;
public:
	PrintableMP(unsigned int MP, int offsetMP)
		: m_increment(offsetMP)
		, m_nextMP(MP)
	{
	}

	virtual MyString toString() const{};
};

class PrintableEffect:public Printable
{
private:
	
public:
	PrintableEffect()
	
	{
	}

	virtual MyString toString() const{};
};

#endif
