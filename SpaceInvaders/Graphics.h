#pragma once

#include <list>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Engine.h"
#include "SpriteComponent.h"

class SpriteComponent;

class Graphics
{
public:
	//dirty Sprite Sheet declarations. Should be replaced with data from a file.
	static const int skSpriteSheetWidth = 128;
	static const int skSpriteSheetHeight = 128;

	//Initialization and clean up functions
	static bool InitGraphics();
	static void CleanGraphics();

	//Render and Asset Loading functions
	static void Render();
	static SDL_Texture *LoadResource(const char* resource);

	static void RegisterSpriteToDraw(SpriteComponent *spriteComp);

	static void RemoveSpriteFromDrawList(SpriteComponent * const spriteComp);

	static void SortByZOrder();

	static void SetSrcRectFromTexture(SDL_Texture *const texture, SDL_Rect & rect);

private:
	Graphics();

	//Private clean up functions to clear out memory
	static void ClearDrawList();

	//Static Render Variable declarations
	static SDL_Surface *spBitmapSurface;
	static SDL_Texture *spBitmapTexture;
	static SDL_Renderer *spRenderer;
	static std::list<SpriteComponent*> *spDrawList;
};