#include "Graphics.h"


SDL_Surface *Graphics::spBitmapSurface = nullptr;
SDL_Texture *Graphics::spBitmapTexture = nullptr;
SDL_Renderer *Graphics::spRenderer = nullptr;

bool Graphics::InitGraphics()
{
	spRenderer = SDL_CreateRenderer(Engine::GetWindow(), -1, SDL_RENDERER_ACCELERATED);

	if (spRenderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize Renderer. Error: %s", SDL_GetError());
	}

	const char* resource = "Resources/Player.PNG";
	if (!LoadResource(resource))
	{
		return false;
	}
	return true;
}

void Graphics::CleanGraphics()
{
	//Clean up Graphics and clear any memory allocated for surfaces and textures
	if (spBitmapTexture != NULL)
	{
		SDL_DestroyTexture(spBitmapTexture);
	}

	if (spRenderer != NULL)
	{
		SDL_DestroyRenderer(spRenderer);
	}
}

void Graphics::Render()
{
	SDL_RenderClear(spRenderer);
	SDL_RenderCopy(spRenderer, spBitmapTexture, NULL, NULL);
	SDL_RenderPresent(spRenderer);
}

bool Graphics::LoadResource(const char* resource)
{
	spBitmapSurface = IMG_Load(resource);
	if (!spBitmapSurface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load Image resource: %s. Error: %s", resource, SDL_GetError());
		return false;
	}

	spBitmapTexture = SDL_CreateTextureFromSurface(spRenderer, spBitmapSurface);
	SDL_FreeSurface(spBitmapSurface);

	return true;
}