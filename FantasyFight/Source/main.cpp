//#include <vld.h> VISUAL LEAK DETECTOR INCLUDE -- not necessary in release
#include "Game.h"

int main()
{
	Game* tehGame = Game::getInstance();	//not a typo

	while(!tehGame -> getFlags().m_singleFlags.f_doExit)
	{
		tehGame -> update();
		tehGame -> render();
	}

	Game::getInstance(true);
}