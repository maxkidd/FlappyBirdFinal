#ifndef _IGAMEOBJECT_H_
#define _IGAMEOBJECT_H_

#include "../Types.h"

class IComponent
{
public:
	virtual ~IComponent() {}
	
	// Returns its type
	virtual ComponentTypes type() = 0;
	
	int entityID;
};

#endif