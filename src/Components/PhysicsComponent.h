#ifndef _PHYSICSCOMPONENT_H_
#define _PHYSICSCOMPONENT_H_

#include "IComponent.h"

class PhysicsComponent : public IComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	
	// Returns COMP_RENDER
	ComponentTypes type();
	
	SpriteIdentifier _id; // ID of the sprite in the char block
	Vector2 _position; // Position relative to the screen
	bool _active; // Whether sprite is visible
	float _angleDegrees; // Angle of rotation
};

#endif