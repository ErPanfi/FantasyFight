#ifndef FANTASYFIGHT_TEAM_H
#define FANTASYFIGHT_TEAM_H

#include "Character.h"

class Team
{
public:
	static const int MAX_TEAM_SIZE = 10;

	//TODO put a private list for this
	Character* m_teamMembers[MAX_TEAM_SIZE];

private:
	int m_currTeamSize;

public:
	Team();

	//team size getter
	int getTeamSize() const		{ return m_currTeamSize; }

	void registerCharacter(Character* newChar);
	void unregisterCharacter(Character* charToDelete);
};

#endif