#include "Logic/BackgroundManager.h"

#include "Systems/EntityManager.h"
#include "Systems/ServiceLocator.h"

#include "gba.h"
#include <cstdlib>


BackgroundManager::BackgroundManager()
{



}
BackgroundManager::~BackgroundManager(){}

void BackgroundManager::Process()
{
	if (_backgrounds.empty())
	{
		// Get all background components (there should only be one)
		vector<IComponent*> backgrounds = ServiceLocator::GetEntityManager()->GetAllComponentsOfType(COMP_BACKGROUND);

		if (backgrounds.size() == 0)
			return;

		// Fill background components
		for (int i = 0; i < backgrounds.size(); i++)
		{
			_backgrounds.push_back((BackgroundComponent*)backgrounds[i]);
		}
	}
	if (_player == NULL)
	{
		// Get all player components (there should only be one)
		vector<IComponent*> players = ServiceLocator::GetEntityManager()->GetAllComponentsOfType(COMP_PLAYER);

		if (players.size() == 0)
			return;

		// player is the first (and only) player
		_player = (PlayerComponent*)players[0];
	}


	// Loop through all backgrounds
	for (int i = 0; i < _backgrounds.size(); i++)
	{
		if (_backgrounds[i]->_background_id == BG_FOREGROUND)
		{
			if (_backgrounds[i]->_reset_tiles)
			{
				_backgrounds[i]->_reset_tiles = false;
				for (int x = 0; x < 32; x++)
				{
					// Sky Tile
					for (int y = 0; y < 12; y++)
					{
						_backgrounds[i]->_tiles[x][y] = 92;
					}
					// Background tiles
					for (int y = 0; y < 5; y++)
					{
						_backgrounds[i]->_tiles[x][y + 12] = (x % 15) + (18 * y);
					}
					// Underneath floor tiles
					for (int y = 0; y < 15; y++)
					{
						_backgrounds[i]->_tiles[x][y + 17] = 200;
					}
				}
			}
		}

		
		// If background is pipes, do random pipe logic and update screen
		if (_backgrounds[i]->_background_id == BG_PIPES)
		{
			if (_backgrounds[i]->_reset_tiles)
			{
				_backgrounds[i]->_reset_tiles = false;
				for (int x = 0; x < 32; x++)
				{
					for (int y = 0; y < 32; y++)
					{
						_backgrounds[i]->_tiles[x][y] = 200;
					}
					// Floor Tiles
					_backgrounds[i]->_tiles[x][17] = 90;
					for (int y = 0; y < 14; y++)
					{
						_backgrounds[i]->_tiles[x][y + 18] = 91;
					}
				}
			}
			//_player->_pixel_distance = _backgrounds[i]->_real_position.x;
			_backgrounds[i]->_real_position.x += _backgrounds[i]->_speed;

			_backgrounds[i]->_integer_position.x = (int)_backgrounds[i]->_real_position.x;
			_backgrounds[i]->_integer_position.y = (int)_backgrounds[i]->_real_position.y;

			int distance = (int)_backgrounds[i]->_real_position.x / 8;

			// Random number for pipes
			int randHeight = rand() % 6;

			// Every 16 tiles, produce a pipe
			if (((int)_backgrounds[i]->_real_position.x % 128) == 0)
			{
				// Clear previous pipe
				for (int x = 0; x < 5; x++)
				{
					for (int y = 0; y < 17; y++)
					{
						_backgrounds[i]->_tiles[(distance + 28 + x) % 32][y] = 200;
					}
				}
				// Display the top pipe
				for (int it = 0; it <= randHeight; it++)
				{
					// Display pipe end top
					if (it == randHeight)
					{
						_backgrounds[i]->_tiles[(distance + 28) % 32][it] = 96;
						_backgrounds[i]->_tiles[(distance + 29) % 32][it] = 97;
						_backgrounds[i]->_tiles[(distance + 30) % 32][it] = 98;
						_backgrounds[i]->_tiles[(distance + 31) % 32][it] = 99;
						_backgrounds[i]->_tiles[(distance + 32) % 32][it] = 100;
						_backgrounds[i]->_tiles[(distance + 28) % 32][it+1] = 101;
						_backgrounds[i]->_tiles[(distance + 29) % 32][it+1] = 102;
						_backgrounds[i]->_tiles[(distance + 30) % 32][it+1] = 103;
						_backgrounds[i]->_tiles[(distance + 31) % 32][it+1] = 104;
						_backgrounds[i]->_tiles[(distance + 32) % 32][it+1] = 105;
					}
					// Display pipe main at the top
					else
					{
						_backgrounds[i]->_tiles[(distance + 29) % 32][it] = 93;
						_backgrounds[i]->_tiles[(distance + 30) % 32][it] = 94;
						_backgrounds[i]->_tiles[(distance + 31) % 32][it] = 95;
					}
				}

				// Display the bottom pipe
				for (int it = randHeight + 10; it <= 16; it++)
				{
					// Display bottom end
					if (it == randHeight + 10)
					{
						_backgrounds[i]->_tiles[(distance + 28) % 32][it - 1] = 106;
						_backgrounds[i]->_tiles[(distance + 29) % 32][it - 1] = 107;
						_backgrounds[i]->_tiles[(distance + 30) % 32][it - 1] = 108;
						_backgrounds[i]->_tiles[(distance + 31) % 32][it - 1] = 109;
						_backgrounds[i]->_tiles[(distance + 32) % 32][it - 1] = 110;
						_backgrounds[i]->_tiles[(distance + 28) % 32][it] = 111;
						_backgrounds[i]->_tiles[(distance + 29) % 32][it] = 112;
						_backgrounds[i]->_tiles[(distance + 30) % 32][it] = 113;
						_backgrounds[i]->_tiles[(distance + 31) % 32][it] = 114;
						_backgrounds[i]->_tiles[(distance + 32) % 32][it] = 115;
					}
					// Display pipe main at the bottom
					else
					{
						_backgrounds[i]->_tiles[(distance + 29) % 32][it] = 93;
						_backgrounds[i]->_tiles[(distance + 30) % 32][it] = 94;
						_backgrounds[i]->_tiles[(distance + 31) % 32][it] = 95;
					}
				}
			}
		}

		if (_backgrounds[i]->_background_id == BG_SCORE)
		{
			if (_backgrounds[i]->_reset_tiles)
			{
				_backgrounds[i]->_reset_tiles = false;
				for (int x = 0; x < 32; x++)
				{
					for (int y = 0; y < 32; y++)
					{
						_backgrounds[i]->_tiles[x][y] = 200;
					}
				}
			}

			_backgrounds[i]->_tiles[10][1] = (_player->_score % 10) + 116;
			_backgrounds[i]->_tiles[9][1] = ((_player->_score / 10) % 10) + 116;
			_backgrounds[i]->_tiles[8][1] = ((_player->_score / 100) % 10) + 116;

			_backgrounds[i]->_tiles[20][1] = (_player->_best_score % 10) + 116;
			_backgrounds[i]->_tiles[19][1] = ((_player->_best_score / 10) % 10) + 116;
			_backgrounds[i]->_tiles[18][1] = ((_player->_best_score / 100) % 10) + 116;
		}


	}

}