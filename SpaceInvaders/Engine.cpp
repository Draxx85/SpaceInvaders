#include "Engine.h"

SDL_Window *Engine::pWindow = nullptr;
SDL_Renderer *Engine::pRenderer = nullptr;
SDL_Surface *Engine::pBitmapSurface = nullptr;
SDL_Texture *Engine::pBitmapTexture = nullptr;

bool Engine::bIsRunning = false;

//Initialize all the main components of the engine
int Engine::InitEngine() 
{
	pWindow = NULL;
	pRenderer = NULL;
	pBitmapSurface = NULL;
	pBitmapTexture = NULL;

	bIsRunning = false;
	if (!SetupSDL()) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL with Error: %s", SDL_GetError());
		bIsRunning = false;
		return 1;
	}

	bIsRunning = true;
	return 0;
}

//Clean up the engine and make sure that all memory is cleanly released
void Engine::CleanEngine()
{
	//Clean up SDL and close the application
	if (pBitmapTexture != NULL)
	{
		SDL_DestroyTexture(pBitmapTexture);
	}
	
	if (pRenderer != NULL)
	{
		SDL_DestroyRenderer(pRenderer);
	}
	
	if (pWindow != NULL)
	{
		SDL_DestroyWindow(pWindow);
	}
	SDL_Quit();
}

bool Engine::SetupSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL with Error: %s", SDL_GetError());
		return false;
	}

	pWindow = SDL_CreateWindow("Space Invaders",				// window title
		SDL_WINDOWPOS_UNDEFINED,								// initial x position
		SDL_WINDOWPOS_UNDEFINED,								// initial y position
		1920,													// width, in pixels
		1080,													// height, in pixels
		0														// flags - see below
	);

	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

	if (pRenderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize Renderer. Error: %s", SDL_GetError());
		return false;
	}
	return true;
}

void Engine::StartEngineLoop()
{
	while (Engine::IsGameRunning()) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				bIsRunning = false;
				break;
			}
		}
	}
}

bool Engine::IsGameRunning()
{
	return bIsRunning;
}