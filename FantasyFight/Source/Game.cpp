#include "Game.h"

Game* Game::m_gameInstance = nullptr;

Game* Game::getInstance()
{
	if(!m_gameInstance)
		m_gameInstance = new Game();

	return m_gameInstance;
}