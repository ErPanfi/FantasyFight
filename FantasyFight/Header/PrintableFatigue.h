#ifndef FANTASYFIGHT_PRINTABLEFATIGUE_H
#define FANTASYFIGHT_PRINTABLEFATIGUE_H

#include "Printable.h"

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

#endif