#ifndef _TYPES_H_
#define _TYPES_H_

#include <stddef.h>
#include <limits.h>

enum ComponentTypes
{
	COMP_RENDER,
	COMP_PLAYER,
	COMP_BACKGROUND
};

enum SpriteSize
{
	SIZE_8X,
	SIZE_16X,
	SIZE_32X,
	SIZE_64X
};

enum SpriteShape
{
	SHAPE_SQUARE,
	SHAPE_HORIZONTAL,
	SHAPE_VERTICAL
};

enum SpriteIdentifier
{
	SPRITE_BIRD,
	SPRITE_CAR
};

enum BackgroundIdentifier
{
	BG_FOREGROUND,
	BG_PIPES,
	BG_SCORE
};


struct Vector2
{
	float x;
	float y;
};

struct Vector2i
{
	int x;
	int y;
};

#define CharBaseBlock(n)                   (((n)*0x4000)+0x6000000)
#define ScreenBaseBlock(n)                (((n)*0x800)+0x6000000)

#define BG_CHAR_BLOCK 0
#define BG_SCREEN_BLOCK0 16
#define BG_SCREEN_BLOCK1 18
#define BG_SCREEN_BLOCK2 20

#define BG_COLOR_PALETTE 0
#define BG_COLOR_256 1
#define BG_COLOR_16 0

#define COLOR_SHIFT 7
#define CHAR_SHIFT 2
#define PAL_SHIFT 7
#define SCREEN_SHIFT 8

#endif