#include "Components\BackgroundComponent.h"

BackgroundComponent::BackgroundComponent(BackgroundIdentifier background, int screen_block, int char_block)
{
	_reset_tiles = true;
	_update_screen = true;
	_speed = 0.55f;
	_screen_bb = screen_block;
	_char_bb = char_block;
	_integer_position.x = 0;
	_integer_position.y = 0;
	_real_position.x = 0.0f;
	_real_position.y = 0.0f;
	_background_id = background;

}

BackgroundComponent::~BackgroundComponent()
{

}

ComponentTypes BackgroundComponent::type()
{
	return COMP_BACKGROUND;
}