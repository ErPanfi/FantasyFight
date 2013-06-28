#ifndef FANTASYFIGHT_AGGRESSIVEBRAIN_H
#define FANTASYFIGHT_AGGRESSIVEBRAIN_H

#include "Brain.h"

class AggressiveBrain : public Brain
{
public:

	virtual Character* buildOwner(g_CharacterClassEnum ownerClass);

protected:
	virtual ActionLibraryRecord* decideAction(Targetable* target = nullptr);
	virtual Targetable* decideTarget(ActionLibraryRecord* actionRecord = nullptr);

};

#endif