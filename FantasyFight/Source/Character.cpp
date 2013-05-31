#include "Character.h"

bool Character::tick ()
{
	return this->currentState();
}

bool Character::stateIdle()
{

	return true;

}

int Character::timeToAction()
{
	return lastTurn + this->initiative();

}

int Character::initiative()
{
	return 10 - this->getDex() + initiativeModifier;
}