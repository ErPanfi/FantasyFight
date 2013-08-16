#include "Arbiter.h"
#include "Game.h"

#include "Character.h"
#include "Action.h"
#include "ActionLibraryRecord.h"
#include "ActiveEffect.h"
#include "Attack.h"

#include "Global.h"
#include "Targetable.h"

#include <cstdlib>	//required for random, and only for that
#include <ctime>	//required for init the random generatoòr with system time
#include <assert.h>

#include "NextCharacterPrintable.h"
#include "PrintableMP.h"
#include "PrintableFatigue.h"

Arbiter::Arbiter()
	: m_fatigueReductionCounter(0)
	, m_winningTeam(Game::TeamEnum::COUNT_TEAMS)
	, m_currCharacterToAct(nullptr)
	, m_nextTurnStep(&Arbiter::nextCharacterToAct)
{
	//Init attributes labels
	m_attributesLabels[g_AttributesEnum::STRENGTH]		= "Strength";
	m_attributesLabels[g_AttributesEnum::DEXTERITY]		= "Dexterity";
	m_attributesLabels[g_AttributesEnum::INTELLIGENCE]	= "Intelligence";
	m_attributesLabels[g_AttributesEnum::DEFENCE]		= "Defence";
	m_attributesLabels[g_AttributesEnum::ACCURACY]		= "Accuracy";
	m_attributesLabels[g_AttributesEnum::COUNT_ATTRIB]	= "Count";
	m_attributesLabels[g_AttributesEnum::MELEE_ACC]		= "Melee accuracy";
	m_attributesLabels[g_AttributesEnum::RANGED_ACC]	= "Ranged accuracy";

	//init turn steps array
	/*
	m_turnCycleSteps[TurnCycleStepEnum::CHOOSE_NEXT_CHARACTER]		= &Arbiter::nextCharacterToAct;
	m_turnCycleSteps[TurnCycleStepEnum::PREPARE_CHARACTER]			= &Arbiter::prepareCharacterForTurn;
	m_turnCycleSteps[TurnCycleStepEnum::EVOLVE_EFFECTS]				= &Arbiter::evolveEffectsOnCharacter;
	m_turnCycleSteps[TurnCycleStepEnum::CHARACTER_CAN_ACT]			= &Arbiter::checkIfCharacterCanAct;
	m_turnCycleSteps[TurnCycleStepEnum::CREATE_NEW_ACTION]			= &Arbiter::registerCharacterNewAction;
	m_turnCycleSteps[TurnCycleStepEnum::CHARGE_CURRENT_ACTION]		= &Arbiter::chargeCharacterAction;
	m_turnCycleSteps[TurnCycleStepEnum::END_CHARACTER_TURN]			= &Arbiter::endCharacterTurn;
	m_turnCycleSteps[TurnCycleStepEnum::CHECK_VICTORY_CONDITIONS]	= &Arbiter::checkVictoryConditions;
	*/
}

void Arbiter::addCharacterToHeap(Character* newChar)
{
	m_characterHeap.add(newChar);
}

void Arbiter::removeCharacterFromHeap(Character* charToRemove)
{
	m_characterHeap.remove(charToRemove);
}

void Arbiter::registerTeamsToHeap()
{
	Game* gamePtr = Game::getInstance();

	Team::TeamCharacterList::Iterator beginIter = gamePtr -> getTeam(Game::TeamEnum::LEFT) -> getActiveMembersIterator();
	Team::TeamCharacterList::Iterator endIter = beginIter.endIterator();
	for(; beginIter != endIter; ++beginIter)
	{
		Character* currChar = *(beginIter.current());
		currChar -> incFatigue();
		addCharacterToHeap(currChar);
	}

	beginIter = gamePtr -> getTeam(Game::TeamEnum::RIGHT) -> getActiveMembersIterator();
	endIter = beginIter.endIterator();
	for(; beginIter != endIter; ++beginIter)
	{
		Character* currChar = *(beginIter.current());
		currChar->incFatigue();
		addCharacterToHeap(currChar);
	}
}

void Arbiter::reduceFatigueOfEveryone()
{
	++m_fatigueReductionCounter %= FATIGUE_REDUCTION_PERIOD;	//epic code line, but still n00b if compared to --(*p)++

	if(!m_fatigueReductionCounter)
	{
		int offset = -(m_characterHeap.top() -> getFatigue());

		Game* gamePtr = Game::getInstance();
		Team::TeamCharacterList::Iterator beginIter = gamePtr -> getTeam(Game::TeamEnum::LEFT) -> getActiveMembersIterator();
		Team::TeamCharacterList::Iterator endIter = beginIter.endIterator();
		for(; beginIter != endIter; ++beginIter)
		{
			Character* currChar = *(beginIter.current());
			currChar -> incFatigue(offset);
		}

		beginIter = gamePtr -> getTeam(Game::TeamEnum::RIGHT) -> getActiveMembersIterator();
		endIter = beginIter.endIterator();
		for(; beginIter != endIter; ++beginIter)
		{
			Character* currChar = *(beginIter.current());
			currChar -> incFatigue(offset);
		}
	}
}

//turn cycle methods
void Arbiter::nextCharacterToAct() 
{
	reduceFatigueOfEveryone();
	m_currCharacterToAct = m_characterHeap.top();
	//m_randomGeneratorInc = 0;

	m_nextTurnStep = &Arbiter::prepareCharacterForTurn;
}

void Arbiter::prepareCharacterForTurn()		//preliminary for turn start
{
	IOManager* ioManager = &IOManager::instance();
	ioManager -> manageOutput(m_currCharacterToAct -> getName() + " has " + m_currCharacterToAct -> getHP() + " HP.");
	unsigned int prevMP = m_currCharacterToAct->getMP();
	m_currCharacterToAct -> incMP();
	ioManager -> manageOutput(new PrintableMP(m_currCharacterToAct->getMP(), (m_currCharacterToAct->getMP() - prevMP)));

	m_nextTurnStep = &Arbiter::evolveEffectsOnCharacter;
}

void Arbiter::evolveEffectsOnCharacter()		//evolution of active effects
{
	Character::CharacterActiveEffectsList::Iterator effectIterator = m_currCharacterToAct -> getActiveEffectsIterator();
	Character::CharacterActiveEffectsList::Iterator endEffectIterator = effectIterator.endIterator();
	for(; effectIterator != endEffectIterator; ++effectIterator)
	{
		ActiveEffect* currActiveEffect = *(effectIterator.current());
		currActiveEffect -> applyRecurringEffect();
		if(currActiveEffect -> canBeRemoved())
		{
			m_currCharacterToAct -> removeActiveEffect(currActiveEffect);
		}
	}

	m_nextTurnStep = &Arbiter::checkIfCharacterCanAct;
}

void Arbiter::checkIfCharacterCanAct()
{
	if(!m_currCharacterToAct -> canActThisTurn())
		m_nextTurnStep = &Arbiter::endCharacterTurn;		//if character can't act end its turn
	else if(m_currCharacterToAct -> getChargingAction())
		m_nextTurnStep = &Arbiter::chargeCharacterAction;	//if it has already an action charge that action
	else
		m_nextTurnStep = &Arbiter::registerCharacterNewAction;		//otherwise a new action is required
}

void Arbiter::registerCharacterNewAction()	//ask the character for a new action and store it
{
	//obtain action from character
	if(!m_currCharacterToAct -> getChargingAction())
	{
		m_currCharacterToAct -> decideNextAction();
	}
	
	if(m_currCharacterToAct -> getChargingAction())
	{
		Action* newAction = m_currCharacterToAct -> getChargingAction();
		MyString message = m_currCharacterToAct -> getName() + " perform " + newAction -> getName() + " on " + (newAction -> getTarget() -> getName());
		IOManager::instance().manageOutput(message);

		//first check if the action targets another action: if so the attack already exists
		if(!(newAction -> getTarget()) || (newAction -> getTarget() -> getTargetType() != g_TargetTypeEnum::ACTION)) //perform check on TypeId first to soften RTTI performance penalty
		{
			m_attackList.push_back(new Attack(newAction));
		}
		else	//otherwise it must be added to existing attack
			((Action*)newAction -> getTarget()) -> getAttack() -> addAnotherAction(newAction);	

		m_nextTurnStep = &Arbiter::chargeCharacterAction;
	}
}

void Arbiter::chargeCharacterAction()			//charge character action and eventually perform the attack
{
	m_currCharacterToAct -> chargeAction();
	IOManager::instance().manageOutput( m_currCharacterToAct -> getChargingAction() -> buildActionChargedPrintable());

	checkAndResolveAttack(m_currCharacterToAct -> getChargingAction() -> getAttack());

	m_nextTurnStep = &Arbiter::endCharacterTurn;
}

void Arbiter::endCharacterTurn()				//prepare character for turn end
{
	unsigned int prevFatigue = m_currCharacterToAct->getFatigue();
	m_currCharacterToAct -> incFatigue();
	IOManager::instance().manageOutput(new PrintableFatigue(m_currCharacterToAct->getFatigue(), (m_currCharacterToAct->getFatigue() - prevFatigue)));
	m_characterHeap.updateTop();
	IOManager::instance().pressEnter();

	m_nextTurnStep = &Arbiter::checkVictoryConditions;
}

//victory condition checking
void Arbiter::checkVictoryConditions()
{
	Game* gamePtr = Game::getInstance();

	if(!(gamePtr -> getTeam(Game::TeamEnum::LEFT) -> getTeamSize()))
	{
		m_winningTeam = Game::TeamEnum::RIGHT;
		m_nextTurnStep = nullptr;
	}
	else if(!(gamePtr -> getTeam(Game::TeamEnum::RIGHT) -> getTeamSize()))
	{
		m_winningTeam = Game::TeamEnum::LEFT;
		m_nextTurnStep = nullptr;
	}
	else
		m_nextTurnStep = &Arbiter::nextCharacterToAct;
}


void Arbiter::checkAndResolveAttack(Attack* attack)
{
	Arbiter::ArbiterAttackList::Iterator attackIter = m_attackList.find(&attack);
	if(attackIter != m_attackList.end() && !attack -> getActionToChargeNum())		//attack is charged!!!
	{
		//get generating action and perform check
		Attack::ActionList::Iterator iter = attack -> getActionIterator();	
		Attack::ActionList::Iterator end = iter.endIterator();

		//if attack contains action they must be resolved
		if(iter != end)
		{
			//copy iterator, preserving begin ptr
			Attack::ActionList::Iterator iterAgain = iter;
			Action* currAction = *(iterAgain.current());		//only first action is to be checked for success
			bool success = currAction -> isActionSuccedeed();	//check succedeed! Action take place
			for(; iterAgain != end; ++iterAgain)	
			{
				if(success)
					currAction -> applyEffectOnTarget();
				else
					IOManager::instance().manageOutput(currAction -> buildFailurePrintable());

				currAction = (++iterAgain) != end ? *(iterAgain.current()) : nullptr;	//iter.current() == nullptr <=> iter == end()
			}
		}

		//now attack have to be removed

		//first notify all characters that its action has been resolved
		for(; iter != end; ++iter)
		{
			(*iter.current()) -> getOwner() -> actionHasBeenResolved(); //this will signal characters to perform cleanup on all their actions
		}

		//then remove attack record from list
		attackIter.remove();

		//and finally it can be deleted
		delete attack;
	}
}

void Arbiter::resetAttackList()
{
	//delete from head
	while(!m_attackList.empty())
	{
		ArbiterAttackList::Iterator iter = m_attackList.begin();
		Attack* currAttack = *iter.current();
		delete currAttack;
		iter.remove();	
	}
}

void Arbiter::performNextTurnStep()
{
	//old, non state-based version
	/*
	Game* gamePtr = Game::getInstance();

	//obtain next character to act
	Character* currCharToAct = nextCharacterToAct();
	IOManager::instance().manageOutput(new Printable(currCharToAct -> getName() + " turn.\n" ));
	//prepare character for turn
	prepareCharacterForTurn(currCharToAct);
	//evolve effect on character
	evolveEffectsOnCharacter(currCharToAct);
	//if character can act 
	if(currCharToAct -> canActThisTurn())
	{
		//if needed an action must be created and inserted in an attack
		if(!currCharToAct -> getChargingAction())
			registerCharacterNewAction(currCharToAct);

		//at this point the character has surely an action to charge up
		chargeCharacterAction(currCharToAct);
	}

	//character turn ends
	endCharacterTurn(currCharToAct);
	//check victory conditions
	checkVictoryConditions();
	//if no one won a new turn can happen
	return m_winningTeam == Game::TeamEnum::COUNT_TEAMS;
	*/

	//exec this turn step iff there is one to exec and the flag is enabled
	(this->*m_nextTurnStep)();
}

void Arbiter::createNewAttackFromAction(Action* generatingAction)
{
	Attack* newAttack = new Attack(generatingAction);
	m_attackList.push_back(newAttack);
}

int Arbiter::getLegalTargetListForAction(ActionLibraryRecord* actionRecord, Character* owner, ArbiterTargetableList* targetList)
{
	int insertedElements = 0;

	Team* alliedTeam = owner -> getTeam();

	//TODO if is too loose, second condition allow for every character to fit in. Revise.
	if(actionRecord -> canTargetThis(g_TargetTypeEnum::ALLIED_CHARACTER) || actionRecord -> canTargetThis(g_TargetTypeEnum::ANY_CHARACTER))
	{
		Team::TeamCharacterList::Iterator iter =  alliedTeam -> getActiveMembersIterator();
		Team::TeamCharacterList::Iterator endIter = iter.endIterator();

		for(; iter != endIter; ++iter)
		{
			if(targetList)	//if targetList is null this function is used for a check for a legal target to exists
				targetList -> push_back((Targetable*)(*(iter.current())));

			insertedElements++;	
		}
	}

	if(actionRecord -> canTargetThis(g_TargetTypeEnum::ENEMY_CHARACTER) || actionRecord -> canTargetThis(g_TargetTypeEnum::ANY_CHARACTER))
	{
		Team::TeamCharacterList::Iterator iter =  alliedTeam -> getEnemyTeam() -> getActiveMembersIterator();
		Team::TeamCharacterList::Iterator endIter = iter.endIterator();

		for(; iter != endIter; ++iter)
		{
			if(targetList)	//if targetList is null this function is used for a check for a legal target to exists
				targetList -> push_back((Targetable*)(*(iter.current())));

			insertedElements++;	
		}
	}

	return insertedElements;
}

inline int Arbiter::randomNumber(int min, int max)
{
	int baseValue = max - min + 1;
	srand((unsigned int) time(0));
//	m_randomGeneratorInc += RANDOM_GENERATOR_INCREMENT;
	return (rand() % baseValue) + min;
}

inline unsigned int Arbiter::performThrowOnAttrib(Character* theCharacter, g_AttributesEnum theAttrib, bool useModifier)
{
	assert(theAttrib != g_AttributesEnum::COUNT_ATTRIB);

	unsigned int baseValue = 0;
	switch(theAttrib)
	{
	case g_AttributesEnum::COUNT_ATTRIB :	//shouldn't be necessary
		return 0;
	case g_AttributesEnum::MELEE_ACC :
		baseValue = theCharacter -> getAttrib(g_AttributesEnum::ACCURACY) + theCharacter -> getAttribModifier(g_AttributesEnum::STRENGTH);
		break;
	case g_AttributesEnum::RANGED_ACC :
		baseValue = theCharacter -> getAttrib(g_AttributesEnum::ACCURACY) + theCharacter -> getAttribModifier(g_AttributesEnum::DEXTERITY);
		break;

	default:
		baseValue = useModifier ? theCharacter -> getAttribModifier(theAttrib) : theCharacter -> getAttrib(theAttrib);
		break;
	}

	return randomNumber(MIN_ATTRIBUTE_THROW_VALUE, baseValue);
}

int Arbiter::performContest(Character* challenger, g_AttributesEnum challengerAttrib, Character* challenged, g_AttributesEnum challengedAttrib)
{
	int result1 = performThrowOnAttrib(challenger, challengerAttrib);
	int result2 = performThrowOnAttrib(challenged, challengedAttrib);
	int result3 = result1 - result2;

	MyString output = MyString("Performed test of ") + m_attributesLabels[challengerAttrib] + " vs " + m_attributesLabels[challengedAttrib] + " with a result of " + result3 + " ( " + result1 + " vs " + result2 + ")";
	IOManager::instance().manageOutput(new Printable(output));

	return result3;
}