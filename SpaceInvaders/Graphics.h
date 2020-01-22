#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Engine.h"
#include "Entity.h"
#include <string>
#include <list>

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
	static std::list<Entity> DrawList;
};