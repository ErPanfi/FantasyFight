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
	int m_currTeamSize;

	//accessible only through game
	friend class Game;	//allow a Game, and only a game, to create teams
	Team();
	//TODO implement copy ctor, dtor and = restrictions

	TeamCharacterList m_teamMembers;

public:

	//team list manager
	int getTeamSize() const		{ return m_currTeamSize; }
	TeamCharacterList::Iterator getMembersIterator() const { return m_teamMembers.begin(); }

	void registerCharacter(Character* newChar);
	void unregisterCharacter(Character* charToDelete);
};

#endif