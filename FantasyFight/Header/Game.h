#ifndef FANTASYFIGHT_GAME_H
#define FANTASYFIGHT_GAME_H

#include "List.h"

//forward declaration
class Team;
class Arbiter;
class ActionLibraryRecord;

class Game
{

public:
	enum TeamEnum
	{
		LEFT = 0,
		RIGHT,
		COUNT_TEAMS,
	};

	static const unsigned int ACTION_LIBRARY_RECORD_LIST_POOL_SIZE = 20;
	typedef List<ActionLibraryRecord*, ACTION_LIBRARY_RECORD_LIST_POOL_SIZE> GameActionLibraryRecordList;

private:
	//members
	Team*		m_teams[TeamEnum::COUNT_TEAMS];
	Arbiter*	m_arbiter;
	GameActionLibraryRecordList	*m_actionLibraryRecords;

	//singleton
	static Game* m_gameInstance;
	//ctors, dtor and = are private: you MUST use getInstance()
	Game();
	Game(const Game& otherGame);
	~Game();
	Game& operator=(const Game& otherGame);

	//init and uninit methods
	Team*		createTeam(Game::TeamEnum teamId, bool autoCreate);
	void		destroyTeams();
	Arbiter*	createArbiter();
	void		destroyArbiter();
	GameActionLibraryRecordList* createActionRecordLibrary();
	void		destroyActionRecordLibrary();

	void proclamateWinner(TeamEnum winner);

public:
	//singleton accessors
	static Game* getInstance();

	void addActionLibraryRecordToList(ActionLibraryRecord* newActionRecord);

	Team* getTeam(TeamEnum teamNum) const;
	Team* getEnemyTeam(TeamEnum teamNum) const;

	void startGame();
};

#endif