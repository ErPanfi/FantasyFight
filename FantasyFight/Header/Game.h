#ifndef FANTASYFIGHT_GAME_H
#define FANTASYFIGHT_GAME_H

#include "List.h"
#include "Global.h"

//forward declaration
class Team;
class Arbiter;
class ActionLibraryRecord;
class CharacterClass;

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
	CharacterClass* classLibrary[g_CharacterClassEnum::COUNT_CHARCLASS];

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
	void		initClassLibrary();
	void		destroyClassLibrary();


	void proclamateWinner(TeamEnum winner);

public:
	//singleton accessors
	static Game*	getInstance();
	Team*			getTeam(TeamEnum teamNum) const;
	Team*			getEnemyTeam(TeamEnum teamNum) const;
	Arbiter*		getArbiter() const { return m_arbiter; }
	CharacterClass* getClassInstance( g_CharacterClassEnum charClass);
	void addActionLibraryRecordToList(ActionLibraryRecord* newActionRecord);
	GameActionLibraryRecordList* getActionLibraryRecordList() const; { return m_actionLibraryRecords; } 

	void startGame();
};

#endif