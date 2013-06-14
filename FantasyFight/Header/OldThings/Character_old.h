#ifndef _Classes_Character_
#define  _Classes_Character_

#include "Entity_old.h"

using namespace std;

enum stateCh { IDLE, ACTIVE};

typedef bool (*ChState)();

class Character:Entity {

protected:
	//string name;
	string classe;
	int lv;
	int hp;
	int mp;
	int strength;
	int intelligence;
	int dexterity;
	int defense;
	int lastTurn;
	//weapon ch_weapon;
	int initiativeModifier;

	stateCh actualState;

	void switchState ();

public:	
	ChState currentState; //stato da utilizzare per le funzioni

	Character(string thisName);

	//virtual void attack () const;
	
	//get
	//string getName () { return name;}
	string getClasse () { return classe;}
	int getHp (){ return hp;}
	int getMp (){ return mp;}
	int getDex (){ return dexterity;}

	void setInitiativeModifier (int val);

	bool stateIdle ();
	bool stateActive ();

	//to get character state
	bool tick();

	//funzione calcolo turno
	int timeToAction ();
	//iniziativa (n)
	int initiative ();

	//status iniziativa
	
};


class Warrior:public Character{

public:
	Warrior(string thisName):Character(thisName){
		classe = "Warrior";
		hp = 100;
		mp = 10;
		strength = 5;
		intelligence = 1;
		dexterity = 3;
		defense = 3;
	}


};


class Mage:public Character{

public:
	Mage(string thisName):Character(thisName){
		classe = "Mage";
		hp = 50;
		mp = 50;
		strength = 2;
		intelligence = 5;
		dexterity = 2;
		defense = 2;
	}


};

class Knight:public Character{

public:
	Knight(string thisName):Character(thisName){
		classe = "Knight";
		hp = 100;
		mp = 30;
		strength = 3;
		intelligence = 2;
		dexterity = 1;
		defense = 5;
	}


};

class Assassin:public Character{

public:
	Assassin(string thisName):Character(thisName){
		classe = "Assassin";
		hp = 50;
		mp = 30;
		strength = 2;
		intelligence = 2;
		dexterity = 5;
		defense = 2;
	}


};


#endif