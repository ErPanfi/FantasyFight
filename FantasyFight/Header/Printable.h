#ifndef FANTASYFIGHT_PRINTABLE_H
#define FANTASYFIGHT_PRINTABLE_H

#include "MyString.h"

class  Printable
{
public:
	 
	virtual MyString toString() const = 0;

private:

	Printable* next;

};

class PrintableCharacter:Printable
{
	virtual MyString toString() const;
};

class PrintableMP:Printable
{
	virtual MyString toString() const;
};

class PrintableCharacter:Printable
{
	virtual MyString toString() const;
};




#endif
