#ifndef _PLAYERDRIVER_H_
#define _PLAYERDRIVER_H_

#include "IEntitySystem.h"
#include "../Components/PlayerComponent.h"

class PlayerDriver : IEntitySystem
{
public:
	PlayerDriver();
	~PlayerDriver();

	void Process();

private:
	PlayerComponent* _player;
	bool KeyPressed;
};
#endif