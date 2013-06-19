#ifndef FANTASYFIGHT_TEAM_H
#define FANTASYFIGHT_TEAM_H

#include "Game.h"
#include "Character.h"
#include "List.h"

class Team
{
public:
	static const int CHAR_TEAM_SIZE = 1; //Take that, da mettere 4
	static const int MAX_TEAM_SIZE = 2 * CHAR_TEAM_SIZE;
	typedef List<Character*, MAX_TEAM_SIZE> TeamCharacterList;

private:

	//accessible only through game
	friend class Game;	//allow a Game, and only a game, to create and destroy teams
	Team(Game::TeamEnum teamID);
	~Team();
	//TODO implement copy ctor and = restrictions

	Game::TeamEnum m_teamID;

	//team composition
	TeamCharacterList m_teamMembers;
	TeamCharacterList m_activeMembers;
	unsigned int m_currTeamSize;


public:

	//team ID
	Game::TeamEnum getTeamID() const { return m_teamID; }
	Team* getEnemyTeam() const { return Game::getInstance() -> getEnemyTeam(m_teamID); }

	//team list manager
	unsigned int getTeamSize() const		{ return m_currTeamSize; }
	TeamCharacterList::Iterator getActiveMembersIterator() const { return m_activeMembers.begin(); }
	TeamCharacterList::Iterator getMembersIterator() const { return m_teamMembers.begin(); }

	//this transfer pointer ownership to team
	void registerCharacter(Character* newChar);
	void unregisterCharacter(Character* charToDelete);
};

#endif