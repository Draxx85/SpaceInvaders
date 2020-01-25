#pragma once

#include <list>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Engine.h"
#include "SpriteComponent.h"

class SpriteComponent;

//If I have time, I should ref count and share textures!
struct STextureRef
{
	SDL_Texture *pTexture;
	std::string resource;
	int RefCount = 0;
};
/////////////////////////////////////////
class Graphics
{
public:
	//dirty Sprite Sheet declarations. Should be replaced with data from a file.
	static const int skSpriteSheetWidth = 128;
	static const int skSpriteSheetHeight = 128;

	static int sWindowWidth;
	static int sWindowHeight;

	//Initialization and clean up functions
	static bool InitGraphics();
	static void CleanGraphics();

	//Render and Asset Loading functions
	static void Render();
	static SDL_Texture *LoadResource(const char* resource);
	static SDL_Texture *LoadText(SDL_Surface* pSurface);

	static SDL_Texture *LoadTextSolid(const char *text, SDL_Color color);

	static SDL_Texture *LoadTextShaded(const char *text, SDL_Color color, SDL_Color shadedColor);

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
	static SDL_Renderer *spRenderer;
	static std::list<SpriteComponent*> *spDrawList;
	static TTF_Font *m_Font;
};