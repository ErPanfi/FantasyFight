#ifndef FANTASYFIGHT_CHARACTER_H
#define FANTASYFIGHT_CHARACTER_H

#include "List.h"
#include "Global.h"
#include "Targetable.h"

class Brain;
class Action;
class ActiveEffect;
class Team;

static const int MIN_ATTRIB_VALUE = 8;

class Character: public Targetable
{
public:
	//effects management
	static const unsigned int EFFECT_POOL_SIZE = 10;
	typedef List<ActiveEffect*, EFFECT_POOL_SIZE> CharacterActiveEffectsList; 


private:

	//attributes
	int m_attributes[g_AttributesEnum::COUNT_ATTRIB];
	int m_fatigue;
	int m_magicPoints;

	//Brain & action members
	Brain*	m_brain;
	Action* m_chargingAction;

	//flags
	unsigned char m_flags;
	static const unsigned char MASK_IS_BLOCKED = 1;
	static const unsigned char MASK_IS_DEAD = MASK_IS_BLOCKED << 1;

	CharacterActiveEffectsList m_activeEffectsList;

	//copy ctors and dtors common code
	void unInit();
	void initFromOtherCharacter(const Character& other);

	Team* m_team;

public:

	static const int DEFAULT_FATIGUE_INCREMENT = 10;

	//ctors, dtor and =
	Character(Brain* characterBrain, Team* team);
	Character(const Character& other);
	~Character();
	Character& operator=(const Character& other);

	//team getter
	Team* getTeam() const { return m_team; }


	//attributes getter & setters
	int inline getAttrib(g_AttributesEnum attrib) const;
	int inline getAttribModifier(g_AttributesEnum attrib) const;
	void inline setAttrib(g_AttributesEnum attrib, int value);

	//status methods
	bool canActThisTurn() const;
	bool inline isDead() const;

	//fatigue getter & setter
	int inline getFatigue() const { return m_fatigue; }
	void inline setFatigue(int newValue) { m_fatigue = newValue; }
	void incFatigue(int offset);
	void incFatigue();
	//function for arbiter heap comparison
	static bool compareFatigue(Character* &lesser, Character* &greater);	

	//MP handling
	int  inline getMP() const		{ return m_magicPoints; }
	void inline setMP(int newValue)	{ m_magicPoints = newValue; }
	void inline incMP(int offset)	{ m_magicPoints += offset; }
	void inline incMP()				{ incMP(getAttribModifier(g_AttributesEnum::INT)); }

	//active effects handling
	void acquireNewEffect(ActiveEffect* newEffect);	//note: this transfer effect ownership to the character!!!
	CharacterActiveEffectsList::Iterator getActiveEffectsIterator() const;	//TODO this must return a const iterator
	void removeActiveEffect(ActiveEffect* targetEffect);


	//brain handling: each character is owner of his brain
	Brain* getBrain() const { return m_brain; }
	//can't set the brain externally, for now

	//action handling: each character is owner of his charging action (can exists only one at time)
	Action* decideNextAction();
	bool isChargingAnAction() const { return m_chargingAction != nullptr; }
	void chargeAction();
	void actionHasBeenResolved();	//this should be call only once an attack has been resolved and it's ready to be disposed

	void setBrainOwner();

};

#endif