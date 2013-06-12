#ifndef FANTASYFIGHT_GAME_H
#define FANTASYFIGHT_GAME_H

#include "Team.h"
#include "Arbiter.h"

class Game
{

public:
	enum TeamEnum
	{
		LEFT = 0,
		RIGHT,
		COUNT_TEAMS,
	};

private:
	//members
	Team	m_teams[TeamEnum::COUNT_TEAMS];
	Arbiter m_arbiter;

	//singleton
	static Game* m_gameInstance;
	Game() {}


public:
	//singleton accessors
	static Game* getInstance();

	Team* getTeam(TeamEnum teamNum) const		{ return const_cast<Team*>(&m_teams[teamNum]); }
	Team* getEnemyTeam(TeamEnum teamNum) const	{ return getTeam(teamNum == TeamEnum::LEFT ? TeamEnum::RIGHT : TeamEnum::LEFT); }

};

#endif