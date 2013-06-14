#ifndef FANTASYFIGHT_CHARACTERCLASS_H
#define FANTASYFIGHT_CHARACTERCLASS_H


#include "List.h"
#include "Action.h"
#include "Global.h"


class CharacterClass
{
public:

	enum CharacterClassEnum
	{
		WARIOR = 0,
		THIEF,
		WIZARD,
		COUNT_CHARCLASS,
	};

	//TODO copy construct, assignment, destructor
	//TODO get attributes
private:

	CharacterClass(int* attributes, List<Action*,10> actions);
	int baseAttributes[COUNT_CHARCLASS]; 
	List<Action*,10> classAction;
	CharacterClass& buildCharClass ( CharacterClassEnum selClass);



};

#endif 