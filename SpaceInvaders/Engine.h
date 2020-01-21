#pragma once

#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_Image.h"

class Engine {
public:
	static int InitEngine();
	static void CleanEngine();
	static void StartEngineLoop();

	static bool IsGameRunning();

private:
	Engine();

	static bool SetupSDL();

	static SDL_Window *pWindow;
	static SDL_Renderer *pRenderer;
	static SDL_Surface *pBitmapSurface;
	static SDL_Texture *pBitmapTexture;

	static bool bIsRunning;
};