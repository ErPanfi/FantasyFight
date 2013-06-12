#include "Team.h"

Team::Team()
	: m_currTeamSize(0)
{

}

void Team::registerCharacter(Character* newChar)
{
	//*(m_teamMembers.getNewObject()) = newChar;
	m_teamMembers[m_currTeamSize++] = newChar;
}

void Team::unregisterCharacter(Character* charToDelete)
{
	int i;
	for(i = 0; i < m_currTeamSize && m_teamMembers[i] != charToDelete; i++);

	if(i < m_currTeamSize)
	{
		m_teamMembers[i] = m_teamMembers[--m_currTeamSize];
	}	
}

