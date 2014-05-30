#ifndef _BACKGROUNDCOMPONENT_H_
#define _BACKGROUNDCOMPONENT_H_

#include "IComponent.h"

class BackgroundComponent : public IComponent
{
public:
	BackgroundComponent(BackgroundIdentifier background, int screen_block, int char_block);
	~BackgroundComponent();
	
	// Returns COMP_RENDER
	ComponentTypes type();
	
	bool _reset_tiles; // set tiles to default screen
	bool _update_screen;
	int _screen_bb;
	int _char_bb;
	float _speed;
	Vector2i _integer_position; // Position between 0 and 256
	Vector2 _real_position;
	int _tiles[32][32];
	BackgroundIdentifier _background_id;
};

#endif