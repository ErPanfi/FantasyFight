#include "Team.h"

Team::Team()
	: m_currTeamSize(0)
{

}

void Team::registerCharacter(Character* newChar)
{
	*(m_teamMembers.getNewObject()) = newChar;
}

void Team::unregisterCharacter(Character* charToDelete)
{
	m_teamMembers.find(&charToDelete).remove();
}