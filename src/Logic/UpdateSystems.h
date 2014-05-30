#ifndef _UPDATESYSTEMS_H_
#define _UPDATESYSTEMS_H_

#include "IEntitySystem.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RenderComponent.h"

class UpdateSystems : IEntitySystem
{
public:
	UpdateSystems();
	~UpdateSystems();

	void Process();

};
#endif