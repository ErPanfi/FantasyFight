#include "AggressiveBrain.h"
#include "Action.h"
#include "Character.h"
#include "Game.h"

Action* AggressiveBrain::buildNewActionForOwner()
{
	Game::GameActionLibraryRecordList* actionLibrary = Game::getInstance() -> getActionLibraryRecordList();
	Game::GameActionLibraryRecordList::Iterator iter = actionLibrary -> begin();
	Game::GameActionLibraryRecordList::Iterator end = actionLibrary -> end();

	ActionLibraryRecord* decidedAction = nullptr;

	//TODO implement intelligent action selection
	while(!decidedAction)
	{
		ActionLibraryRecord* currAction = *(iter.current());

	}
}

Character* AggressiveBrain::buildOwner(g_CharacterClassEnum ownerClass)
{
	g_AttributesEnum attribPrio[G_PRIORITIZABLE_ATTRIBS];

	switch (ownerClass)
	{
	case WARRIOR:
		attribPrio[0] = g_AttributesEnum::STR;
		attribPrio[1] = g_AttributesEnum::DEX;
		attribPrio[2] = g_AttributesEnum::INT;
		break;
	case THIEF:
		attribPrio[0] = g_AttributesEnum::DEX;
		attribPrio[1] = g_AttributesEnum::INT;
		attribPrio[2] = g_AttributesEnum::STR;
		break;
	case WIZARD:
		attribPrio[0] = g_AttributesEnum::INT;
		attribPrio[1] = g_AttributesEnum::DEX;
		attribPrio[2] = g_AttributesEnum::STR;
		break;
	default:
		return nullptr;
	}

	return  new Character(this, ownerClass, attribPrio);
}