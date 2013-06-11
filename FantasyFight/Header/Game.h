#ifndef FANTASYFIGHT_GAME_H
#define FANTASYFIGHT_GAME_H

#include "Arbiter.h"
#include "Team.h"

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
	/*
	Team* inline getTeam(TeamEnum teamNum) const		{ return &m_teams[teamNum]; }
	Team* inline getEnemyTeam(TeamEnum teamNum) const	{ return getTeam(teamNum == TeamEnum::LEFT ? TeamEnum::RIGHT : TeamEnum::LEFT); }
	*/
};

#endif