#include "Character.h"

int inline Character::getAttrib(AttributesEnum attrib) const
{
	Debug.assert(attrib < AttributesEnum.Count, "Attributes index out of range");
}
