#include "Logic/PlayerDriver.h"

#include "Systems/EntityManager.h"
#include "Systems/ServiceLocator.h"

#include "gba.h"

#include <vector>

PlayerDriver::PlayerDriver() 
{
	_player = NULL;
	KeyPressed = false;
}
PlayerDriver::~PlayerDriver(){}

void PlayerDriver::Process()
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

	//Update pixel distance
	_player->_pixel_distance++;

	// Update score
	_player->_score = _player->_pixel_distance / 128;
	// Reset player if dead
	if (_player->_dead)
	{
		_player->_pixel_distance = 0;
		if (_player->_score > _player->_best_score)
		{
			_player->_best_score = _player->_score;
		}
		_player->_dead = false;
	}


	// Simulate gravity
	_player->_velocity.y += 0.03f;


	if(_player->_angleDegrees > -45)
	{
		--_player->_angleDegrees;
	}
	
	// If KEY_A pressed flappybird goes up
	if ((REG_KEYINPUT & KEY_A) == 0 && !KeyPressed)
	{
		KeyPressed = true;
		_player->_velocity.y = -_player->_max_speed;
		_player->_angleDegrees = 45;
	}
	else if ((REG_KEYINPUT & KEY_A) != 0)
	{
		KeyPressed = false;
	}
	/*if ((REG_KEYINPUT & KEY_UP) == 0)
	{
		_player->_velocity.y = 0.2;
	}
	if ((REG_KEYINPUT & KEY_DOWN) == 0)
	{
		_player->_velocity.y = -0.2;
	}*/
}