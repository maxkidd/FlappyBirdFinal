#ifndef _BACKGROUNDMANAGER_H_
#define _BACKGROUNDMANAGER_H_

#include "IEntitySystem.h"
#include "../Components/BackgroundComponent.h"
#include "../Components/PlayerComponent.h"
#include <vector>

class BackgroundManager : IEntitySystem
{
public:
	BackgroundManager();
	~BackgroundManager();

	void Process();

private:
	std::vector<BackgroundComponent*> _backgrounds;
	PlayerComponent* _player;
};
#endif