#include "Game.h"
#include "Arbiter.h"
#include "Team.h"

Game::Game()
{
}

Game* Game::m_gameInstance = nullptr;

Game* Game::getInstance()
{
	if(!m_gameInstance)
		m_gameInstance = new Game();

	return m_gameInstance;
}

void Game::startGame()
{
	m_arbiter = createArbiter();
	m_teams[TeamEnum::LEFT] = createTeam(TeamEnum::LEFT, false);
	m_teams[TeamEnum::RIGHT] = createTeam(TeamEnum::RIGHT, true);

}

Team* Game::getTeam(TeamEnum teamNum) const		
{ 
	return const_cast<Team*>(m_teams[teamNum]); 
}

Team* Game::getEnemyTeam(TeamEnum teamNum) const	
{ 
	return getTeam(teamNum == TeamEnum::LEFT ? TeamEnum::RIGHT : TeamEnum::LEFT); 
}

Arbiter* Game::createArbiter()
{
	return new Arbiter();
}

Team* Game::createTeam(Game::TeamEnum teamId, bool autoCreate)
{
	Team* newTeam = new Team(teamId);
	//TODO add characters to team
	//newTeam -> registerCharacter(aCharacter);

	return newTeam;
}
