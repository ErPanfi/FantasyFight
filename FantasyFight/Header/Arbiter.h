﻿#ifndef FANTASYFIGHT_ARBITER_H
#define FANTASYFIGHT_ARBITER_H

#include "Heap.h"
#include "Game.h"
#include "Character.h"
#include "Printable.h"
#include "List.h"
#include "IOManager.h"

class Attack;
class Targetable;
class ActionLibraryRecord;

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
	void resetHeap() { m_characterHeap = ArbiterCharacterHeap(); }	//accessible from Game

	//turn cycle methods and state management
	typedef void (Arbiter::*TurnStepFn)();

	//turn cycle tracking
	Character* m_currCharacterToAct;
	TurnStepFn m_nextTurnStep;

	//turn cycle methods
	void nextCharacterToAct();										//select next character to act and save it to m_currCharacterToAct
	void prepareCharacterForTurn(/*Character* theCharacter*/);		//preliminary for turn start
	void evolveEffectsOnCharacter(/*Character* theCharacter*/);		//evolution of active effects
	void checkIfCharacterCanAct();									//check if character can act on this turns and if a decision is needed
	void registerCharacterNewAction(/*Character* theCharacter*/);	//ask the character for a new action and store it
	void chargeCharacterAction(/*Character* theCharacter*/);		//charge character action and eventually perform the attack
	void endCharacterTurn(/*Character* theCharacter*/);				//prepare character for turn end
	void checkVictoryConditions();									//check if match is ended

	//victory handling
	Game::TeamEnum m_winningTeam;

	//attacks management section: arbiter is owner of all attacks in here
	static const int ATTACK_POOL_SIZE = MAX_HEAP_SIZE;
	typedef List<Attack*, ATTACK_POOL_SIZE> ArbiterAttackList;
	ArbiterAttackList m_attackList;
	void createNewAttackFromAction(Action* generatingAction);	//create a new attack from the given generating action
	void checkAndResolveAttack(Attack* attack);
	void resetAttackList();

	//attributes translations
	MyString m_attributesLabels[g_AttributesEnum::COUNT_COMPOSITE];

	////randomness improvement
	//static const unsigned int RANDOM_GENERATOR_INCREMENT = 1234;
	//unsigned int m_randomGeneratorInc;
public:

	//heap composition
	void registerTeamsToHeap();
	void addCharacterToHeap(Character* newChar);
	void removeCharacterFromHeap(Character* charToRemove);

	//turn cycle methods
	void resetFSM() 
	{
		resetHeap();
		resetAttackList();
		m_nextTurnStep = &Arbiter::nextCharacterToAct; 
	}
	void performNextTurnStep();	//perform the whole game turn and return true if the game can continue	
	Game::TeamEnum getWinningTeam() const { return m_winningTeam; }

	//target acquiring methods manager
	static const unsigned int TARGETABLE_LIST_POOL_SIZE = 10;
	typedef List<Targetable*, TARGETABLE_LIST_POOL_SIZE> ArbiterTargetableList;
	int getLegalTargetListForAction(ActionLibraryRecord* actionRecord, Character* owner, ArbiterTargetableList* targetList = nullptr);

	//test methods
	static const unsigned int MIN_ATTRIBUTE_THROW_VALUE = 1;
	inline int randomNumber(int min, int max);
	inline unsigned int performThrowOnAttrib(Character* theCharacter, g_AttributesEnum theAttrib, bool useModifier = false);
	int performContest(Character* challenger, g_AttributesEnum challengerAttrib, Character* challenged, g_AttributesEnum challengedAttrib);

	//IO interfaces
	/*
	inline void output(Printable* toOutput)					const { IOManager::instance().manageOutput(toOutput); }
	inline void output(Entity&	entity)						const { IOManager::instance().manageOutput(entity); }
	inline Entity* input(Entity::EntityList& alternatives)	const { return IOManager::instance().manageInput(alternatives); }
	*/
};

#endif