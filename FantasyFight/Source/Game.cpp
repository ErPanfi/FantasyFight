#include "Game.h"
#include "Arbiter.h"
#include "Team.h"
#include "ActionLibraryRecord.h"

Game::Game()
{
	m_arbiter = createArbiter();
	m_teams[TeamEnum::LEFT] = createTeam(TeamEnum::LEFT, false);
	m_teams[TeamEnum::RIGHT] = createTeam(TeamEnum::RIGHT, true);
	m_actionLibraryRecords = createActionRecordLibrary();
}

Game::~Game()
{
	destroyArbiter();
	destroyTeams();
	destroyActionRecordLibrary();
}

Game* Game::getInstance()
{
	//singleton
	static Game* m_gameInstance = nullptr;

	if(!m_gameInstance)
		m_gameInstance = new Game();

	return m_gameInstance;
}

Team* Game::getTeam(TeamEnum teamNum) const		
{ 
//	return const_cast<Team*>(m_teams[teamNum]); 
	return m_teams[teamNum]; 
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

void Game::destroyArbiter()
{
	delete m_arbiter;
}

void Game::destroyTeams()
{
	delete m_teams[TeamEnum::LEFT];
	delete m_teams[TeamEnum::RIGHT];
}

Game::GameActionLibraryRecordList* Game::createActionRecordLibrary()
{
	return new GameActionLibraryRecordList();
}

void	Game::destroyActionRecordLibrary()
{
	GameActionLibraryRecordList::Iterator iter = m_actionLibraryRecords -> begin();
	GameActionLibraryRecordList::Iterator endIter = m_actionLibraryRecords -> end();

	for(; iter != endIter; ++iter)
		delete (*iter.current());		//destroy all the associated action records

	delete m_actionLibraryRecords;	//this will free all the resources from memory pool
}

void Game::addActionLibraryRecordToList(ActionLibraryRecord* newActionRecord)
{
	m_actionLibraryRecords -> push_back(newActionRecord);
}

void Game::startGame()
{
	while(m_arbiter -> performTurnCycle());

	proclamateWinner(m_arbiter -> getWinningTeam());
}

void Game::proclamateWinner(TeamEnum winner)
{
}
