#include "Entity.h"

Entity::Entity (string theName)
{
	static int idCount = 0;
	idCount ++;
	id = idCount;

	name = theName;

};

