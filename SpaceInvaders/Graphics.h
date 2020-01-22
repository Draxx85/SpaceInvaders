#pragma once

#include <list>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Engine.h"
#include "SpriteComponent.h"

struct SVector2D
{
	float x;
	float y;
};

struct STransform
{
	SVector2D *Position;
	SVector2D *Scale;
	float angle;
};

class Graphics
{
public:
	static bool InitGraphics();
	static void CleanGraphics();
	static void Render();
	static bool LoadResource(const char* resource);

private:
	Graphics();
	static SDL_Surface *spBitmapSurface;
	static SDL_Texture *spBitmapTexture;
	static SDL_Renderer *spRenderer;
	static std::list<SpriteComponent*> *spDrawList;
};