#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "IEntitySystem.h"

#include "../Components/PlayerComponent.h"
#include "../Components/RenderComponent.h"
#include "../Components/BackgroundComponent.h"

#include <vector>

class CollisionSystem : IEntitySystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void Process();

private:
	PlayerComponent* _player;
	BackgroundComponent* _pipes_background;
	BackgroundComponent* _foreground_background;
};
#endif