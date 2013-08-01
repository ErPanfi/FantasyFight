#ifndef FANTASYFIGHT_HUMANBRAIN_H
#define FANTASYFIGHT_HUMANBRAIN_H

#include "Brain.h"

class HumanBrain : public Brain
{
private:

	//two-step decision process, in order to fit into update-render main loop
	ActionLibraryRecord*	m_actionLibraryRecord;
	Targetable*				m_target;

	void resetActionBuilder()
	{
		m_actionLibraryRecord = nullptr;
		m_target = nullptr;
	}

protected:
	virtual ActionLibraryRecord* decideAction(Targetable* target = nullptr);
	virtual Targetable* decideTarget(ActionLibraryRecord* actionRecord = nullptr);

public:
	//action deciding
	virtual Action* buildNewActionForOwner() final;

	//create a new Character and become its brain
	virtual Character* buildOwner(g_CharacterClassEnum ownerClass);

	HumanBrain();
};

#endif