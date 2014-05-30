#ifndef _RENDERCOMPONENT_H_
#define _RENDERCOMPONENT_H_

#include "IComponent.h"

class RenderComponent : public IComponent
{
public:
	RenderComponent(SpriteIdentifier id);
	~RenderComponent();
	
	// Returns COMP_RENDER
	ComponentTypes type();
	
	SpriteIdentifier _id; // ID of the sprite in the char block
	Vector2 _position; // Position relative to the screen
	bool _active; // Whether sprite is visible
	int _angleDegrees; // Angle of rotation
};

#endif