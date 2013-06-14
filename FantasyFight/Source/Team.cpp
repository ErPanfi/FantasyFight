#include "Team.h"

Team::Team()
	: m_currTeamSize(0)
{

}

Team::~Team()
{
	//delete all the characters in the team (Team is the owner of character ptrs)
	TeamCharacterList::Iterator endIter  = m_teamMembers.end();
	for(TeamCharacterList::Iterator iter = m_teamMembers.begin(); iter != endIter; ++iter)
	{
		delete *(iter.current());
	}

}

//this transfer pointer ownership to team
void Team::registerCharacter(Character* newChar)
{
	m_teamMembers.push_back(newChar);
	m_activeMembers.push_back(newChar);
	m_currTeamSize++;
}

void Team::unregisterCharacter(Character* charToDelete)
{
	TeamCharacterList::Iterator iter = m_activeMembers.find(&charToDelete);

	if(iter)
	{
		iter.remove();
		m_currTeamSize--;
	}
}

