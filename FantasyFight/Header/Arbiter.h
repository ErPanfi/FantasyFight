#ifndef FANTASYFIGHT_ARBITER_H
#define FANTASYFIGHT_ARBITER_H

#include "Heap.h"
#include "Game.h"
#include "Character.h"

class Attack;
class Targetable;

class Arbiter
{
private:

	//accessible only through game
	friend class Game;	//make creation pf arbiter by game access
	Arbiter();
	//TODO implement copy ctor, dtor and = restrictions

	//fatigue handling and character action ordering
	static const int MAX_HEAP_SIZE = 16;
	typedef Heap<Character*, MAX_HEAP_SIZE, Character::compareFatigue > ArbiterCharacterHeap;
	ArbiterCharacterHeap m_characterHeap;
	static const int FATIGUE_REDUCTION_PERIOD = 100;
	int	 m_fatigueReductionCounter;
	void reduceFatigueOfEveryone();

	//turn cycle methods
	Character* nextCharacterToAct();							//select next character to act
	void prepareCharacterForTurn(Character* theCharacter);		//preliminary for turn start
	void evolveEffectsOnCharacter(Character* theCharacter);		//evolution of active effects
	void registerCharacterNewAction(Character* theCharacter);	//ask the character for a new action and store it
	void handleActiveAttacks(Character* theCharacter);			//charge character action and eventually perform the attack
	void endCharacterTurn(Character* theCharacter);				//prepare character for turn end

	//victory flag
	Game::TeamEnum m_winningTeam;
	void checkVictoryConditions();

	//attacks management section: arbiter is owner of all attacks in here
	static const int ATTACK_POOL_SIZE = MAX_HEAP_SIZE;
	List<Attack*, ATTACK_POOL_SIZE> m_attackList;
	void createNewAttackFromAction(Action* generatingAction);	//create a new attack from the given generating action

public:

	//heap composition
	void registerTeamsToHeap();
	void addCharacterToHeap(Character* newChar);
	void removeCharacterFromHeap(Character* charToRemove);

	//turn cycle methods
	bool performTurnCycle();		//perform the whole game turn and return true if the game can continue	
	Game::TeamEnum getWinningTeam() const { return m_winningTeam; }

	//target acquiring methods manager
	static const unsigned int TARGETABLE_LIST_POOL_SIZE = 10;
	typedef List<Targetable*, TARGETABLE_LIST_POOL_SIZE> ArbiterTargetableList;
	int getLegalTargetListForAction(Action* action, Targetable* targetVector[], int maxBufferSize = Action::MAX_TARGET_BUFFER_SIZE);
};

#endif