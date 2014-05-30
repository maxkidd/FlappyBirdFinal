#include "Components\PlayerComponent.h"

PlayerComponent::PlayerComponent()
{
	_dead = false;
	_score = 0;
	_best_score = 0;
	_pixel_distance = 0;
	_max_speed = 1.3f;
	_acceleration = 0.01f;
	_position.x = 50.0f;
	_position.y = 50.0f;
	_velocity.x = 0.0f;
	_velocity.y = 0.0f;
	_angleDegrees = 0.0f;
}

PlayerComponent::~PlayerComponent()
{

}

ComponentTypes PlayerComponent::type()
{
	return COMP_PLAYER;
}