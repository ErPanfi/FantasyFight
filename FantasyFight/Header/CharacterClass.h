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
		WARRIOR = 0,
		THIEF,
		WIZARD,
		COUNT_CHARCLASS,
	};

	//TODO copy construct, assignment, destructor
	//TODO get attributes
	CharacterClass& buildCharClass ( CharacterClassEnum selClass);

private:

	CharacterClass(int* attributes, List<Action*,10> actions);
	int baseAttributes[COUNT_ATTRIB]; 
	List<Action*,10> classAction;
};

#endif 