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

private:


};

class PrintableCharacter:public Printable
{
private:
	MyString m_name;
	unsigned int m_MP;
	unsigned int m_HP;

public:
	PrintableCharacter( MyString name, unsigned int HP,unsigned int MP)
		: m_name(name)
		,m_MP(MP)
		,m_HP(HP)
	{
	}

	virtual MyString toString() const;
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

	virtual MyString toString() const;
};

class PrintableEffect:public Printable
{
private:
	
public:
	PrintableEffect()
	
	{
	}

	virtual MyString toString() const;
};

class PrintableFatigue:public Printable
{
private:
	int m_increment;
	unsigned int m_nextFatigue;

public:
	PrintableFatigue(unsigned int fatigue, int offsetFatigue)
		: m_increment(offsetFatigue)
		, m_nextFatigue(fatigue)
	{
	}

	virtual MyString toString() const;
};

class PrintableAction:public Printable
{
private:
	

public:
	PrintableAction()
	{
	}

	virtual MyString toString() const;
};

#endif
