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
	static SDL_Window* GetWindow();

private:
	Engine();

	static bool SetupSDL();

	static SDL_Window *spWindow;

	static bool bIsRunning;
};