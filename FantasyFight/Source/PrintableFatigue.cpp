#include "PrintableFatigue.h"

MyString PrintableFatigue::toString() const
{
	return MyString( "Increment Fatigue: ") + m_increment + "\nActual Fatigue: "+m_nextFatigue;
}