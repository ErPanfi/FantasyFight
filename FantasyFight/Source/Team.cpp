#include "Team.h"

Team::Team()
	: m_currTeamSize(0)
{

}

void Team::registerCharacter(Character* newChar)
{
	m_teamMembers.push_back(newChar);
	m_currTeamSize++;
}

void Team::unregisterCharacter(Character* charToDelete)
{
	TeamCharacterList::Iterator iter = m_teamMembers.find(&charToDelete);

	if(iter)
	{
		iter.remove();
		m_currTeamSize--;
	}
}

