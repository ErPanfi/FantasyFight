#include "IOManager.h"

void IOManager::manageOutput(Entity::EntityList& list)
{
	OutputManager::instance().sendOnScreen(list);
}

Entity* IOManager::manageInput(Entity::EntityList& list)
{
	OutputManager::instance().sendOnScreen(list);
	return InputManager::instance().selectedOnScreen(list);
}
