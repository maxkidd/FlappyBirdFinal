#ifndef _PLAYERCOMPONENT_H_
#define _PLAYERCOMPONENT_H_

#include "IComponent.h"

class PlayerComponent : public IComponent
{
public:
	PlayerComponent();
	~PlayerComponent();
	
	// Returns COMP_RENDER
	ComponentTypes type();
	
	bool _dead;
	int _score;
	int _best_score;
	int _pixel_distance;
	float _max_speed;
	float _acceleration;
	Vector2 _position; // Position relative to the screen
	Vector2 _velocity;
	float _angleDegrees; // Angle of rotation
};

#endif