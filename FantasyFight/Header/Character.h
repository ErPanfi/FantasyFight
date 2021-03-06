#ifndef FANTASYFIGHT_CHARACTER_H
#define FANTASYFIGHT_CHARACTER_H

#include "List.h"
#include "Global.h"
#include "Targetable.h"
#include "MyString.h"
#include "Team.h"
#include "Entity.h"

#include "TotalDefenseEffect.h"

class Brain;
class Action;
class ActiveEffect;
class Team;
class CharacterClass;

static const int MIN_ATTRIB_VALUE = 8;

class Character: public Targetable//, public Entity
{
public:
	//effects management
	static const unsigned int EFFECT_POOL_SIZE = 10;
	typedef List<ActiveEffect*, EFFECT_POOL_SIZE> CharacterActiveEffectsList; 

	static const int STRONG_ATTRIB_INCREMENT = 4;
	static const int MILD_ATTRIB_INCREMENT = 2;
	static const int WEAK_ATTRIB_INCREMENT = -2;


private:

	//Brain & action members
	Brain*	m_brain;
	Action* m_chargingAction;
	CharacterClass*	m_characterClass;

	//attributes
	int m_attributes[g_AttributesEnum::COUNT_ATTRIB];
	int m_fatigue;
	int m_magicPoints;
	int m_maxMagicPoints;
	int m_healthPoints;
	int m_maxHealthPoints;
	//MyString m_name; inherited from MyString

	//flags
	typedef unsigned char CharacterFlags;
	CharacterFlags m_flags;
	static const CharacterFlags MASK_EMPTY = 0;
	static const CharacterFlags MASK_IS_BLOCKED = 1;
	static const CharacterFlags MASK_IS_DEAD = MASK_IS_BLOCKED << 1;

	CharacterActiveEffectsList m_activeEffectsList;

	//copy ctors and dtors common code
	void unInit();
	void initFromOtherCharacter(const Character& other);

	Team* m_team;
	void setTeam(Team* newValue) { m_team = newValue;}
	friend void Team::registerCharacter(Character* newChar);

public:

	static const int DEFAULT_FATIGUE_INCREMENT = 10;

	//ctors, dtor and =
	Character(MyString name, Brain* characterBrain, g_CharacterClassEnum characterClass, g_AttributesEnum attributute_priorities[G_PRIORITIZABLE_ATTRIBS]);
	Character(const Character& other);
	~Character();
	Character& operator=(const Character& other);

	//team getter
	Team* getTeam() const { return m_team; }

	//attributes getter & setters
	static const unsigned int STR_TO_HP_MULTIPLIER = 3;
	static const unsigned int INT_TO_MP_MULTIPLIER = 3;
	unsigned int inline getAttrib(g_AttributesEnum attrib) const;
	int inline getAttribModifier(g_AttributesEnum attrib) const;
	void inline setAttrib(g_AttributesEnum attrib, int value);
	//MyString getName () { return m_name; } inherited from MyString
	void setName ( MyString in_name ) { m_name = in_name; }
	/*void setName ( char* in_name ) { m_name}*/
	

	//status methods
	bool canActThisTurn() const;
	bool inline isDead() const;
	virtual inline g_TargetTypeEnum getTargetType() const { return g_TargetTypeEnum::ANY_CHARACTER; }
	CharacterClass* getCharacterClass() const { return m_characterClass; }

	//fatigue getter & setter
	int inline getFatigue() const { return m_fatigue; }
	void inline setFatigue(int newValue) { m_fatigue = newValue; }
	void incFatigue(int offset);
	void incFatigue();
	int calcFatigueIncrement() const;

	//function for arbiter heap comparison
	static bool compareFatigue(Character* &lesser, Character* &greater);	

	//MP handling
	int inline getMP() const		{ return m_magicPoints; }
	void inline setMP(int newValue)	{ m_magicPoints = newValue; }
	void inline incMP(int offset)	
	{ 
		m_magicPoints += offset; 
		if(m_magicPoints > m_maxMagicPoints)
			m_magicPoints = m_maxMagicPoints;
	}

	void inline incMP()				
	{ 
		int inc = getAttribModifier(g_AttributesEnum::INTELLIGENCE);
		incMP(inc > 0 ? inc : 1); 
	}

	//HP handling
	int inline getHP() const		{ return m_healthPoints; }
	void inline setHP(int newValue)	{ m_healthPoints = newValue; }
	void inline incHP(int offset)	
	{ 
		m_healthPoints += offset; 
		if(m_healthPoints > m_maxHealthPoints)
			m_healthPoints = m_maxHealthPoints;
	}

	void receiveDamage(unsigned int damage);

	//active effects handling
	void acquireNewEffect(ActiveEffect* newEffect);	//note: this transfer effect ownership to the character!!!
	CharacterActiveEffectsList::Iterator getActiveEffectsIterator() const;	//TODO this must return a const iterator
	void removeActiveEffect(ActiveEffect* targetEffect);
	//friend declarations for effects
	friend void TotalDefenseEffect::applyAssignmentEffect();
	friend void TotalDefenseEffect::applyDestructionEffect();
	


	//brain handling: each character is owner of his brain
	Brain* getBrain() const { return m_brain; }
	//can't set the brain externally, for now

	//action handling: each character is owner of his charging action (can exists only one at time)
	void decideNextAction();
	Action* getChargingAction() const { return m_chargingAction; }
	void chargeAction();
	void actionHasBeenResolved();	//this should be call only once an attack has been resolved and it's ready to be disposed

	//void setBrainOwner();

	//handling Input\Output
	//virtual Entity& selectedEntity() const; already defined in base class
	virtual Printable* printEntity() const;

};

#endif