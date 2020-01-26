#pragma once

#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_Image.h"
#include "Graphics.h"
#include "UpdateManager.h"
#include "InputManager.h"
#include "ChunkMaster.h"

#define SAFE_DELETE(p)	{if (p)	{ delete (p); (p) = nullptr; } }

class Engine {
public:
	static int InitEngine();
	static void CleanEngine();
	static void StartEngineLoop();

	static bool IsGameRunning();
	static SDL_Window* GetWindow();

	static float sCurrentFramePerSecond;

	static ChunkMaster *sColliderChunks;

private:
	Engine();

	static bool SetupSDL();

	static SDL_Joystick* sGameController;

	static SDL_Window *spWindow;
	static void HandleEvents(SDL_Event &e);

	static void UpdateDeltaTime();

	static bool bIsRunning;

	//Frame Counter
	static float sFrameRate;
	static Uint32 sStartTime;
	static float sDeltaTime;
	static float const TimedUpdateInterval;
	static float TimedUpdateElapsed;
};