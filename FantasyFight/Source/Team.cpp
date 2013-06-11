#include "Team.h"

Team::Team()
	: m_teamMembers(new List<Character*, MAX_TEAM_SIZE>())
	, m_currTeamSize(0)
{

}

void Team::registerCharacter(Character* newChar)
{
	*(m_teamMembers -> getNewObject()) = newChar;
}