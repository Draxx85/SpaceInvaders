#pragma once

#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_Image.h"
#include "Graphics.h"
#include "UpdateManager.h"
#include "InputManager.h"


class Engine {
public:
	static int InitEngine();
	static void CleanEngine();
	static void StartEngineLoop();

	static bool IsGameRunning();
	static SDL_Window* GetWindow();

	static float sCurrentFramePerSecond;

private:
	Engine();

	static bool SetupSDL();

	static SDL_Window *spWindow;
	static void HandleEvents(SDL_Event &e);

	static void UpdateDeltaTime();

	static bool bIsRunning;

	//Frame Counter
	static float sFrameRate;
	static Uint32 sStartTime;
	static float sDeltaTime;
};