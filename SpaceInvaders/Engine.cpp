#include "Engine.h"

//temp
#include <sstream>

#define _DISPLAY_FPS_ 1

SDL_Window *Engine::spWindow = nullptr;
SDL_Joystick *Engine::sGameController = nullptr;

bool Engine::bIsRunning = false;

float Engine::sFrameRate = 0;
Uint32 Engine::sStartTime = 0;
float Engine::sDeltaTime = 0;
float const Engine::TimedUpdateInterval = 0.025f;
float Engine::TimedUpdateElapsed = 0.0f;

//Initialize all the main components of the engine
int Engine::InitEngine() 
{
	bIsRunning = false;

	if (!SetupSDL()) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL with Error: %s", SDL_GetError());
		bIsRunning = false;
		return 1;
	}

	UpdateManager::Init();
	if (!Graphics::InitGraphics())
	{
		return 1;
	}

	InputManager::Init();

	bIsRunning = true;

	if (SDL_NumJoysticks() < 1)
	{
		printf("Warning: No joysticks connected!\n");
	}
	else
	{
		//Load joystick
		sGameController = SDL_JoystickOpen(0);
		if (sGameController == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
	}

	return 0;
}

//Clean up the engine and make sure that all memory is cleanly released
void Engine::CleanEngine()
{	
	UpdateManager::Clean();
	Graphics::CleanGraphics();
	
	if (spWindow != NULL)
	{
		SDL_DestroyWindow(spWindow);
	}
	SDL_Quit();
}

bool Engine::SetupSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL with Error: %s", SDL_GetError());
		return false;
	}

	spWindow = SDL_CreateWindow("Space Invaders",				// window title
		SDL_WINDOWPOS_UNDEFINED,								// initial x position
		SDL_WINDOWPOS_UNDEFINED,								// initial y position
		Graphics::sWindowWidth,									// width, in pixels
		Graphics::sWindowHeight,								// height, in pixels
		0														// flags
	);

	return true;
}

//This is the main loop for the game. All object updates will occur here.
void Engine::StartEngineLoop()
{
	sDeltaTime = 0.0f;
	SDL_Event sdl_event;
	sStartTime = SDL_GetTicks();
	while (Engine::IsGameRunning())
	{
		HandleEvents(sdl_event);
		UpdateManager::Update(sDeltaTime);
		
		if (TimedUpdateElapsed >= TimedUpdateInterval) 
		{
			UpdateManager::TimedUpdate(TimedUpdateElapsed);
			TimedUpdateElapsed = 0.0f;
		}

		Graphics::Render();
		//UpdateUI
		//Graphics::RenderUI();

		UpdateDeltaTime();
	}
}

void Engine::HandleEvents(SDL_Event &e)
{
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
			case SDL_APP_TERMINATING:
			{
				bIsRunning = false;
				return;
			}
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				InputManager::ListenForKeyPress(e);
			default:
				break;
		}
	}
}

inline bool Engine::IsGameRunning()
{
	return bIsRunning;
}

SDL_Window* Engine::GetWindow()
{
	if (spWindow != NULL)
	{
		return spWindow;
	}
	return NULL;
}

inline void Engine::UpdateDeltaTime()
{
	sDeltaTime = (float)(SDL_GetTicks() - sStartTime) /1000;	    
	
	if (sDeltaTime != 0)
	{
		sFrameRate = 1 / sDeltaTime;
	}
	sStartTime = SDL_GetTicks();
	TimedUpdateElapsed += sDeltaTime;

#if _DISPLAY_FPS_ //Display fps Counter on window frame
	std::stringstream fps;
	fps << "Space Invaders || FPS: " << sFrameRate << " DeltaTime: " << sDeltaTime;
	SDL_SetWindowTitle(spWindow, fps.str().c_str()); //gross
#endif 

}