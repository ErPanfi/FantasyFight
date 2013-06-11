#include "Team.h"

Team::Team()
	: m_currTeamSize(0)
{
}

void Team::registerCharacter(Character* newChar)
{
	m_teamMembers[m_currTeamSize++] = newChar;
}