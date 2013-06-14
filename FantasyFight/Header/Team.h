#ifndef FANTASYFIGHT_TEAM_H
#define FANTASYFIGHT_TEAM_H

#include "Game.h"
#include "Character.h"
#include "List.h"

class Team
{
public:
	static const int MAX_TEAM_SIZE = 10;
	typedef List<Character*, MAX_TEAM_SIZE> TeamCharacterList;

private:

	//accessible only through game
	friend class Game;	//allow a Game, and only a game, to create and destroy teams
	Team();
	~Team();
	//TODO implement copy ctor and = restrictions

	//team composition
	TeamCharacterList m_teamMembers;
	TeamCharacterList m_activeMembers;
	unsigned int m_currTeamSize;


public:

	//team list manager
	unsigned int getTeamSize() const		{ return m_currTeamSize; }
	TeamCharacterList::Iterator getActiveMembersIterator() const { return m_activeMembers.begin(); }

	//this transfer pointer ownership to team
	void registerCharacter(Character* newChar);
	void unregisterCharacter(Character* charToDelete);
};

#endif