#ifndef FANTASYFIGHT_TEAM_H
#define FANTASYFIGHT_TEAM_H

#include "Character.h"

class Team
{
public:
	static const int MAX_TEAM_SIZE = 10;

private:
	Character* m_teamMembers[MAX_TEAM_SIZE];
	int m_currTeamSize;

public:
	Team();

	void registerCharacter(Character* newChar);
};

#endif