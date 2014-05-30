#include "Types.h"

#include "Components/RenderComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/BackgroundComponent.h"

#include "Systems/ServiceLocator.h"
#include "Systems/EntityManager.h"
#include "Systems/GraphicsManager.h"

#include "Logic/PlayerDriver.h"
#include "Logic/UpdateSystems.h"
#include "Logic/BackgroundManager.h"
#include "Logic/CollisionSystem.h"

#include "Res/pipe_end_top.h"
#include "Res/pipe_end_bot.h"
#include "Res/pipe_main.h"
#include "Res/bird.h"
#include "Res/palette.h"
#include "Res/background.h"
#include "Res/ground.h"
#include "Res/sky.h"
#include "Res/numbers.h"


int main()
{
	// Initialise display information
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_OBJ | DCNT_OBJ_1D;

	// Setup background controller
	REG_BG0CNT = (BG_COLOR_256 << COLOR_SHIFT) | (BG_SCREEN_BLOCK0 << SCREEN_SHIFT)
		| (BG_COLOR_PALETTE << PAL_SHIFT) | (BG_CHAR_BLOCK << CHAR_SHIFT) | BG_PRIO(2);
	REG_BG1CNT = (BG_COLOR_256 << COLOR_SHIFT) | (BG_SCREEN_BLOCK1 << SCREEN_SHIFT)
		| (BG_COLOR_PALETTE << PAL_SHIFT) | (BG_CHAR_BLOCK << CHAR_SHIFT) | BG_PRIO(1);
	REG_BG2CNT = (BG_COLOR_256 << COLOR_SHIFT) | (BG_SCREEN_BLOCK2 << SCREEN_SHIFT)
		| (BG_COLOR_PALETTE << PAL_SHIFT) | (BG_CHAR_BLOCK << CHAR_SHIFT) | BG_PRIO(0);



	// Draw handler
	GraphicsManager graphics_manager;
	graphics_manager.SetupSprite(SPRITE_BIRD, birdTiles, birdTilesLen / 64, SHAPE_SQUARE, SIZE_16X);
	graphics_manager.SetupPalette(palette, palLen / 4);
	graphics_manager.SetupTiles(backgroundTiles, backgroundTilesLen / 64);
	graphics_manager.SetupTiles(groundTiles, groundTilesLen / 64);
	graphics_manager.SetupTiles(skyTiles, skyTilesLen / 64);
	graphics_manager.SetupTiles(pipe_mainTiles, pipe_mainTilesLen / 64);
	graphics_manager.SetupTiles(pipe_end_topTiles, pipe_end_topTilesLen / 64);
	graphics_manager.SetupTiles(pipe_end_botTiles, pipe_end_botTilesLen / 64);
	graphics_manager.SetupTiles(numbersTiles, numbersTilesLen / 64);

	
	// Entity manager
	EntityManager entity_manager;

	// Service Locator
	ServiceLocator::ProvideEntityManager(&entity_manager);

	// Initialise Entity's and attach Components TODO
	unsigned int FlappyBird = entity_manager.CreateEntity();
	// FlappyBird is an renderable object
	entity_manager.AddComponent(FlappyBird, new RenderComponent(SPRITE_BIRD));
	entity_manager.AddComponent(FlappyBird, new PlayerComponent());
	
	unsigned int foreground = entity_manager.CreateEntity();
	entity_manager.AddComponent(foreground, new BackgroundComponent(BG_FOREGROUND, BG_SCREEN_BLOCK0, 0));

	unsigned int pipes = entity_manager.CreateEntity();
	entity_manager.AddComponent(pipes, new BackgroundComponent(BG_PIPES, BG_SCREEN_BLOCK1, 0));

	unsigned int score = entity_manager.CreateEntity();
	entity_manager.AddComponent(score, new BackgroundComponent(BG_SCORE, BG_SCREEN_BLOCK2, 0));

	// Get game systems (ai, collision) TODO
	PlayerDriver player_driver;
	UpdateSystems update_systems;
	BackgroundManager background_manager;
	CollisionSystem collisions;
	while(true)
	{
		//WaitVSync();
		// Check events
		
		// Run systems to update components
		player_driver.Process();
		background_manager.Process();
		collisions.Process();

		// Update all systems to have the same values
		update_systems.Process();

		// Copy components position and rotation to RenderComponent

		// Draw components
		graphics_manager.Draw(&entity_manager);
	}
}