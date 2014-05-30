#include "Logic/CollisionSystem.h"

#include "Systems/EntityManager.h"
#include "Systems/ServiceLocator.h"

#include "gba.h"

#include <vector>
#include <cmath>

CollisionSystem::CollisionSystem()
{

}
CollisionSystem::~CollisionSystem()
{

}
void CollisionSystem::Process()
{
	if (_player == NULL)
	{
		// Get all player components (there should only be one)
		vector<IComponent*> players = ServiceLocator::GetEntityManager()->GetAllComponentsOfType(COMP_PLAYER);

		if (players.size() == 0)
			return;

		// player is the first (and only) player
		_player = (PlayerComponent*)players[0];
	}
	if (_pipes_background == NULL)
	{
		vector<IComponent*> backgrounds = ServiceLocator::GetEntityManager()->GetAllComponentsOfType(COMP_BACKGROUND);
		
		if (backgrounds.size() == 0)
			return;

		for (int i = 0; i < backgrounds.size(); i++)
		{
			if (((BackgroundComponent*)backgrounds[i])->_background_id == BG_PIPES)
			{
				_pipes_background = (BackgroundComponent*)backgrounds[i];
			}
		}
	}

	if (_foreground_background == NULL)
	{
		vector<IComponent*> backgrounds = ServiceLocator::GetEntityManager()->GetAllComponentsOfType(COMP_BACKGROUND);

		if (backgrounds.size() == 0)
			return;

		for (int i = 0; i < backgrounds.size(); i++)
		{
			if (((BackgroundComponent*)backgrounds[i])->_background_id == BG_FOREGROUND)
			{
				_foreground_background = (BackgroundComponent*)backgrounds[i];
			}
		}
	}

	bool death = false;

	Vector2i player_real_position[4];
	player_real_position[0].x = ((int)_player->_position.x + _pipes_background->_integer_position.x);
	player_real_position[0].y = ((int)_player->_position.y + _pipes_background->_integer_position.y) + 2; // + 2 so it's more realistic collision

	player_real_position[1].x = ((int)_player->_position.x + _pipes_background->_integer_position.x) + 16;
	player_real_position[1].y = ((int)_player->_position.y + _pipes_background->_integer_position.y) + 2; // + 2 so it's more realistic collision

	player_real_position[2].x = ((int)_player->_position.x + _pipes_background->_integer_position.x);
	player_real_position[2].y = ((int)_player->_position.y + _pipes_background->_integer_position.y) + 14; // + 14 so it's more realistic collision

	player_real_position[3].x = ((int)_player->_position.x + _pipes_background->_integer_position.x) + 16;
	player_real_position[3].y = ((int)_player->_position.y + _pipes_background->_integer_position.y) + 14; // + 14 so it's more realistic collision


	for (int i = 0; i < 4; i++)
	{
		int tileX = ((player_real_position[i].x) / 8) % 32;
		int tileY = ((player_real_position[i].y) / 8) % 32;
		int tileId = _pipes_background->_tiles[tileX][tileY];
		if (tileId >= 93 
			&& tileId <= 114 
			&& tileId != 111 
			&& tileId != 96 
 			&& tileId != 100 
			&& tileId != 101 
			&& tileId != 105 
			&& tileId != 106 
			&& tileId != 110)
		{
			death = true;
		}
	}
	if (((player_real_position[3].y / 8) % 32) >= 17)
		death = true;

	if (death == true)
	{
		for (int i = 0; i < 50; i++)
			WaitVSync();
		_player->_dead = true;
		_player->_position.y = 50.0f;
		_player->_velocity.y = 0.0f;
		_pipes_background->_reset_tiles = true;
		_foreground_background->_reset_tiles = true;
	}

}