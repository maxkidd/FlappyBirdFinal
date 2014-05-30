#include "Components/RenderComponent.h"

RenderComponent::RenderComponent(SpriteIdentifier id)
{
	_id = id;
	_active = true;
	_position.x = 50.0f;
	_position.y = 50.0f;
	_angleDegrees = 45;
}


RenderComponent::~RenderComponent()
{
}

ComponentTypes RenderComponent::type()
{
	return COMP_RENDER;
}