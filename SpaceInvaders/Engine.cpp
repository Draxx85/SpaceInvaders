#include "Engine.h"
#include "Graphics.h"
#include "UpdateManager.h"

SDL_Window *Engine::spWindow = nullptr;

bool Engine::bIsRunning = false;
double Engine::sElapsedTime = 0.0f;
int Engine::sFrameCount = 0;
double sStartTime = 0.0f;

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

	bIsRunning = true;
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
		1920,													// width, in pixels
		1080,													// height, in pixels
		0														// flags
	);

	return true;
}

//This is the main loop for the game. All object updates will occur here.
void Engine::StartEngineLoop()
{
	float time = 0.0f;

	while (Engine::IsGameRunning())
	{
		//Handle Input
		UpdateManager::Update(time);
		//if (Timed Update is ready) 
		//{
			//UpdateManager::TimedUpdate() 
		//}

		//AnimationUpdate() maybe....

		//This is temp code!
		SDL_Event e;
		if (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_QUIT) 
			{
				bIsRunning = false;
				break;
			}
		}
		////
		//LateUpdate() Maybe
		Graphics::Render();
		//Graphics::RenderUI();
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