#ifndef FANTASYFIGHT_GAME_H
#define FANTASYFIGHT_GAME_H

#include "List.h"
#include "Global.h"
#include "Entity.h"

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

	//flags management
	typedef unsigned char Bitmask;

	enum GameStateEnum
	{
		GAME_TO_START = 0,
		GAME_STARTED,
		WINNER_TO_BE_PROCLAMATED,
		GAME_ENDED
	};

	union FlagsMask
	{		
		//these are the mask content
		Bitmask m_wholeMask;
		struct singleFlags
		{
			bool f_performNextTurnStep : 1;
			bool f_doExit : 1;
		} m_singleFlags;
		
		//default constructor can be private because the owner is friend and can access it
		FlagsMask()
			: m_wholeMask(0)
		{}
	};

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

	//state handling and functions
	FlagsMask m_flags;
	typedef void (Game::*StateFn)();

	StateFn m_stateFn;

	void initGame();
	void proclamateWinnerAndPrompt();
	void performArbiterCycle();

	class GameEndedPromptChoice : public Entity
	{
	public:
		enum PossibleChoices
		{
			NEW_GAME = 0,
			EXIT,
			COUNT
		} m_choice;

		GameEndedPromptChoice(MyString _label, PossibleChoices _choice)
			: Entity(_label)
			, m_choice(_choice)
		{}
		GameEndedPromptChoice()
			: Entity("NoLabel")
			, m_choice(PossibleChoices::COUNT)
		{}
	};

	Entity::EntityList m_endGameChoices;
	Entity* m_choiceSelected;

	void cleanGameDataAndDecideIfExit();

public:
	//singleton accessors
	static Game*	getInstance(bool _deleteIt = false);
	Team*			getTeam(TeamEnum teamNum) const;
	Team*			getEnemyTeam(TeamEnum teamNum) const;
	Arbiter*		getArbiter() const { return m_arbiter; }
	CharacterClass* getClassInstance( g_CharacterClassEnum charClass);
	void addActionLibraryRecordToList(ActionLibraryRecord* newActionRecord);
	GameActionLibraryRecordList* getActionLibraryRecordList() const { return m_actionLibraryRecords; } 

	//game state management methods
	void update();
	void render();

	inline FlagsMask getFlags() const { return m_flags; }
};

#endif