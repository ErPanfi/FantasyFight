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
	//ENEMY_ITEM,	doesn't exists yet
	ALLIED_ITEM,
	TARGET_COUNT,
};

#endif