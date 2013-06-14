#ifndef FANTASYFIGHT_GLOBAL_H
#define FANTASYFIGHT_GLOBAL_H

enum g_AttributesEnum
{
	STR = 0,
	DEX,
	INT,
	COUNT_ATTRIB,
};

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

#endif