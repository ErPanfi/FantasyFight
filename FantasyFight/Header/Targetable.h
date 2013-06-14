#ifndef FANTASYFIGHT_TARGETABLE_H
#define FANTASYFIGHT_TARGETABLE_H

#include "Global.h"

class Targetable
{
public:
	virtual inline g_TargetTypeEnum getTargetType() const = 0;
};

#endif