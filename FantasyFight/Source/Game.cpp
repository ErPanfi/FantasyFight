#include "Game.h"
#include "Arbiter.h"
#include "Team.h"
#include "ActionLibraryRecord.h"
#include "Brain.h" //Take that
#include "CharacterClass.h"

Game::Game()
	: m_choiceSelected(nullptr)
	, m_stateFn(&Game::initGame)
{
	m_arbiter = createArbiter();
	m_actionLibraryRecords = createActionRecordLibrary();
	initClassLibrary();

	//these will be destroyed in destructor
	m_endGameChoices.push_back(new GameEndedPromptChoice("Altra partita", GameEndedPromptChoice::PossibleChoices::NEW_GAME));
	m_endGameChoices.push_back(new GameEndedPromptChoice("Esci", GameEndedPromptChoice::PossibleChoices::EXIT));
}

Game::~Game()
{
	destroyArbiter();
	destroyTeams();
	destroyActionRecordLibrary();
	destroyClassLibrary();

	//as promised in ctor
	for(Entity::EntityList::Iterator iter = m_endGameChoices.begin(); iter != m_endGameChoices.end(); ++iter)
	{
		delete *iter.current();
	}
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
	return new Arbiter();	//Game is the owner of arbiter
}

void Game::destroyArbiter()
{
	delete m_arbiter;
}

Team* Game::createTeam(Game::TeamEnum teamId, bool humanTeam)
{
	Team* newTeam = new Team(teamId);
	//switch autoCreate Take that
	for ( int i = 0; i < Team::CHAR_TEAM_SIZE; i++)
	{
		Character* newCharacter;

		newCharacter = Brain::buildABrain(humanTeam) -> buildOwner(g_CharacterClassEnum::WARRIOR);// CharacterClass::randomClass());

		newTeam -> registerCharacter(newCharacter);
	}

	return newTeam;		//Game is the owner of team
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

void Game::initGame()
{
	//create teams and register them to heap
	m_teams[TeamEnum::LEFT] = createTeam(TeamEnum::LEFT, true);
	m_teams[TeamEnum::RIGHT] = createTeam(TeamEnum::RIGHT, false);
	m_arbiter -> registerTeamsToHeap();
	m_arbiter -> resetFSM();
	m_flags.m_singleFlags.f_performNextTurnStep = true;
	m_stateFn = &Game::performArbiterCycle;
}

void Game::performArbiterCycle()
{
	if(m_flags.m_singleFlags.f_performNextTurnStep)
	{
		m_arbiter -> performNextTurnStep();
		if(m_arbiter -> getWinningTeam() != TeamEnum::COUNT_TEAMS)
			m_stateFn = &Game::proclamateWinnerAndPrompt;
	}
}

void Game::update()
{	
	//call the state function
	if(m_stateFn)
		(this ->* m_stateFn)();
}

void Game::render()
{
	IOManager::instance().flush();
}

void Game::proclamateWinnerAndPrompt()
{
	TeamEnum winner = m_arbiter -> getWinningTeam();
	MyString message( winner == TeamEnum::LEFT ? "Left" : "Right");
	IOManager::instance().manageOutput(message + " team won!");

	IOManager::instance().manageOutput(MyString("What do you want to do?"));
	IOManager::instance().manageInput(m_endGameChoices, &m_choiceSelected);

	m_stateFn = &Game::cleanGameAndDecideIfExit;
}

void Game::cleanGameAndDecideIfExit()
{
	GameEndedPromptChoice* choiceMade = (GameEndedPromptChoice*) m_choiceSelected;
	switch (choiceMade -> m_choice)
	{
	case GameEndedPromptChoice::PossibleChoices::NEW_GAME:
		m_stateFn = &Game::initGame;
		break;
	default:
		m_flags.m_singleFlags.f_doExit = true;
		break;
	}
}



CharacterClass* Game::getClassInstance(g_CharacterClassEnum charClass)
{
	assert(charClass < g_CharacterClassEnum::COUNT_CHARCLASS);

	if(!classLibrary[charClass])
	{
		switch (charClass)
		{
		case WARRIOR:
			{
				unsigned int attribs[] = {14, 12, 12, 5, 5};
				classLibrary[charClass] = new CharacterClass(attribs, charClass, 30, 10);
			}
			break;
		case THIEF:
			{
				unsigned int attribs[] = {12, 14, 12, 3, 5};
				classLibrary[charClass] = new CharacterClass(attribs, charClass, 25, 15);
			}
			break;
		case WIZARD:
			{
				unsigned int attribs[] = {12, 12, 14, 3, 4};
				classLibrary[charClass] = new CharacterClass(attribs, charClass, 20, 20);
			}
			break;
		default:
			classLibrary[charClass] = nullptr;
			break;
		}
	}

	return classLibrary[charClass];
}

void Game::initClassLibrary()
{
	for(int i = 0; i < g_CharacterClassEnum::COUNT_CHARCLASS; ++i)
		classLibrary[i] = nullptr;
}

void Game::destroyClassLibrary()
{
	for(int i = 0; i < g_CharacterClassEnum::COUNT_CHARCLASS; ++i)
		delete classLibrary[i];
}