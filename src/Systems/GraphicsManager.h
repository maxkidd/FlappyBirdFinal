#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_

#include "../gba.h"
#include "../Types.h"
#include "EntityManager.h"
#include "../Components/IComponent.h"
#include <vector>

#define FIX_SHIFT       8
#define FIX_SCALE       ( 1<<FIX_SHIFT		)
#define FIX_SCALEF      ( (float)FIX_SCALE	)

using std::vector;


struct SpriteDefinition
{
	SpriteSize size;
	SpriteShape shape;
	uint16_t char_bb_identifier;
	uint16_t index;
};

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	void SetupGraphics();
	// Draw all entities according to their components
	void Draw(EntityManager* entity_manager);

	void SetupSprite(SpriteIdentifier index, const unsigned short* tiles, int tilesAmount, SpriteShape shape, SpriteSize size);
	void SetupTiles(const unsigned short* tiles, int tilesAmount);
	// Setup object palette
	void SetupPalette(const unsigned short* pal, int palLength);

private:
	SpriteDefinition GetSpriteDefinition(SpriteIdentifier index);
	void DisplayTile(uint16_t x, uint16_t y, uint8_t tile, uint16_t screenBB);

	int32_t float2fx(float f);

	const int TILE_SIZE = 8 * 8 * 2;
	uint16_t* tileCharBB = (uint16_t*)CharBaseBlock(BG_CHAR_BLOCK);
	uint16_t _sprite_identifier;
	uint16_t* _object_char_bb;
	uint16_t* _background_char_bb;
	vector<SpriteDefinition> _sprite_def;
};

#endif