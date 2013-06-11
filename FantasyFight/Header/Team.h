#ifndef FANTASYFIGHT_TEAM_H
#define FANTASYFIGHT_TEAM_H

#include "Character.h"
#include "List.h"

class Team
{
public:
	static const int MAX_TEAM_SIZE = 10;

private:
	List<Character*, MAX_TEAM_SIZE> m_teamMembers;
	int m_currTeamSize;

public:
	Team();

	void registerCharacter(Character* newChar);
	void unregisterCharacter(Character* charToDelete);
};

#endif