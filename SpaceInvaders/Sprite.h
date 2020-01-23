#pragma once
#include "SDL.h"

class Sprite
{
public:
	static const int skSpriteWidth = 128;
	static const int skSpriteHeight = 128;

	Sprite();
	~Sprite();

	Sprite &operator++();
	Sprite operator++(int);

	Sprite &operator--();
	Sprite operator--(int);

	SDL_Rect SpriteSrcRect;
	SDL_Rect SpriteDestRect;
	SDL_Texture *pBitmapTexture;
	
	int zOrder = 0;
	int m_MaxFrames;
	int m_CurrentFrame = 0;

private:
	void NextFrame();
	void PreviousFrame();
};