#ifndef FANTASYFIGHT_GLOBAL_H
#define FANTASYFIGHT_GLOBAL_H

enum g_AttributesEnum
{
	STRENGTH = 0,
	DEXTERITY,
	INTELLIGENCE,
	DEFENCE,
	ACCURACY,
	COUNT_ATTRIB,	//all the memorized attributes
	//now starting with composite attributes
	MELEE_ACC,
	RANGED_ACC,
	COUNT_COMPOSITE,
};

const unsigned int G_PRIORITIZABLE_ATTRIBS = g_AttributesEnum::INTELLIGENCE + 1;

enum g_TargetTypeEnum
{
	NO_TARGET = 0,
	ENEMY_CHARACTER,
	ALLIED_CHARACTER,
	ANY_CHARACTER,
	ALLIED_ITEM,
	//ENEMY_ITEM,	doesn't exists yet
	//ANY_ITEM,		no sense up to now
	TARGET_COUNT,
};

enum g_CharacterClassEnum
{
	WARRIOR = 0,
	THIEF,
	WIZARD,
	COUNT_CHARCLASS,
};

#endif