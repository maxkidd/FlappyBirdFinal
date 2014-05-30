#include "Systems/GraphicsManager.h"
#include "Components/RenderComponent.h"
#include "Components/BackgroundComponent.h"
#include "gba.h"
#include <cmath>

GraphicsManager::GraphicsManager()
{
	_sprite_identifier = 0;
	_object_char_bb = (uint16_t*)CharBaseBlock(4);
	_background_char_bb = (uint16_t*)CharBaseBlock(BG_CHAR_BLOCK);
	SetupGraphics(); 
}

GraphicsManager::~GraphicsManager(){}

void GraphicsManager::SetupGraphics()
{

	

	ClearObjects();
}


int32_t GraphicsManager::float2fx(float f)
{	return (int32_t)(f*FIX_SCALEF);	}

void GraphicsManager::Draw(EntityManager* entity_manager)
{
	// Check for new renderable entities TODO

	// Get all renderable components
	vector<IComponent*> renderable_components = entity_manager->GetAllComponentsOfType(COMP_RENDER);

	int i = 0;
	// Iterate through the object components
	for (vector<IComponent*>::iterator it = renderable_components.begin(); it != renderable_components.end(); ++it)
	{
		RenderComponent* renderableComponent = (RenderComponent*)(*it);
		SpriteDefinition spriteDef = GetSpriteDefinition(renderableComponent->_id);

		int x = renderableComponent->_position.x;
		int y = renderableComponent->_position.y;

		if (x < 0)
			x = 511 + x;
		if (y < 0)
			y = 255 + y;

			
		
		SetObject(i, (spriteDef.shape << 14) | ATTR0_Y(y) | ATTR0_8BPP | ATTR0_AFF,
			ATTR1_SIZE(spriteDef.size) | ATTR1_X(x) | ATTR1_AFF(0),
			ATTR2_PALBANK(0) | ATTR2_ID4(spriteDef.char_bb_identifier));
		
		ObjAffine* renderAffine = &( (ObjAffine*) ObjBuffer)[0];
	
	
		//float theta = (float)(++player.angleDegrees % 360) * (M_PI/180);
		float angle = (float)(renderableComponent->_angleDegrees % 360) * (M_PI / 180);
		renderAffine->pa = float2fx( cos(angle) );
		renderAffine->pb = float2fx( -sin(angle) );	
		renderAffine->pc = float2fx( sin(angle) );
		renderAffine->pd = float2fx( cos(angle) );
		
		++i;
	}
	UpdateObjects();

	// Get all background components
	vector<IComponent*> background_components = entity_manager->GetAllComponentsOfType(COMP_BACKGROUND);

	// Iterate through the background components
	for (vector<IComponent*>::iterator it = background_components.begin(); it != background_components.end(); ++it)
	{
		BackgroundComponent* backgroundComponent = (BackgroundComponent*)(*it);

		
		// Scroll background
		if (backgroundComponent->_background_id == BG_PIPES)
		{
			REG_BG1HOFS = backgroundComponent->_integer_position.x;
		}
		
		// Update tiles
		if (backgroundComponent->_background_id == BG_PIPES || backgroundComponent->_background_id == BG_SCORE)
		{
			
			for (int x = 0; x < 32; x++)
			{
				for (int y = 0; y < 32; y++)
				{
					DisplayTile(x, y, backgroundComponent->_tiles[x][y], backgroundComponent->_screen_bb);
				}
			}
		}
		
		if (backgroundComponent->_update_screen)
		{
			for (int x = 0; x < 32; x++)
			{
				for (int y = 0; y < 32; y++)
				{
					DisplayTile(x, y, backgroundComponent->_tiles[x][y], backgroundComponent->_screen_bb);
				}
			}
			backgroundComponent->_update_screen = false;
		}
	}

}

SpriteDefinition GraphicsManager::GetSpriteDefinition(SpriteIdentifier index)
{
	for (size_t i = 0; i < _sprite_def.size(); i++)
	{
		if (_sprite_def[i].index == index)
			return _sprite_def[i];
	}
	return SpriteDefinition();
}

void GraphicsManager::SetupSprite(SpriteIdentifier index, const unsigned short* tiles, int tilesAmount, SpriteShape shape, SpriteSize size)
{
	_sprite_def.push_back({ size, shape, _sprite_identifier, index });

	for (uint16_t i = 0; i < tilesAmount * 32; i++)
	{
		_object_char_bb[i] = tiles[i];
	}

	_object_char_bb += tilesAmount * 32;

	_sprite_identifier += tilesAmount;
}
void GraphicsManager::SetupTiles(const unsigned short* tiles, int tilesAmount)
{
	for (int i = 0; i < tilesAmount * 32; i++)
	{
		_background_char_bb[i] = tiles[i]; // bg
	}

	_background_char_bb += tilesAmount * 32;
}


void GraphicsManager::SetupPalette(const unsigned short* pal, int palLength)
{
	for (uint16_t i = 0; i < palLength; i++)
	{
		REG_PALETTE_OBJ[i] = (uint16_t)pal[i];
		REG_PALETTE_BG[i] = (uint16_t)pal[i];
	}
}

void GraphicsManager::DisplayTile(uint16_t x, uint16_t y, uint8_t tile, uint16_t screenBB)
{
	uint16_t* ScreenBB = (uint16_t*)ScreenBaseBlock(screenBB);
	ScreenBB[x + (32 * y)] = tile;
}