#pragma once
#include "SDL.h"

class Sprite
{
public:
	static const int skSpriteWidth = 128;
	static const int skSpriteHeight = 128;
	static const int skSpritesPerRow = 8;

	Sprite();
	Sprite(int maxFrames);
	~Sprite();

	Sprite &operator++();
	Sprite &operator++(int);

	Sprite &operator--();
	Sprite &operator--(int);

	SDL_Rect SpriteSrcRect;
	SDL_Rect SpriteDestRect;
	SDL_Texture *pBitmapTexture;
	
	void FreeTexture();

	int zOrder = 0;
	int m_MaxFrames = 1;
	int m_CurrentFrame = 0;
	int m_SpriteSheetIndex;

private:
	void UpdateFrame();
};