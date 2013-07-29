#ifndef FANTASYFIGHT_TARGETABLE_H
#define FANTASYFIGHT_TARGETABLE_H

#include "Global.h"
#include "Entity.h"

class Targetable : public Entity
{
public:
	Targetable(MyString name)
		: Entity(name)
	{}

	virtual inline g_TargetTypeEnum getTargetType() const = 0;
};

#endif