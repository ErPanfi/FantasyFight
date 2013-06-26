#ifndef FANTASYFIGHT_AGGRESSIVEBRAIN_H
#define FANTASYFIGHT_AGGRESSIVEBRAIN_H

#include "Brain.h"

class AggressiveBrain : public Brain
{
public:

	virtual Action* buildNewActionForOwner();
	virtual Character* buildOwner(g_CharacterClassEnum ownerClass);
};

#endif