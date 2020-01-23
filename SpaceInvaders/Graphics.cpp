#include "Graphics.h"

SDL_Surface *Graphics::spBitmapSurface = nullptr;
//this is temp and should be stored in the sprite
SDL_Texture *Graphics::spBitmapTexture = nullptr;
SDL_Renderer *Graphics::spRenderer = nullptr;
std::list<SpriteComponent *> *Graphics::spDrawList = nullptr;

bool Graphics::InitGraphics()
{
	spRenderer = SDL_CreateRenderer(Engine::GetWindow(), -1, SDL_RENDERER_ACCELERATED);

	if (spRenderer == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize Renderer. Error: %s", SDL_GetError());
	}

	spDrawList = new std::list<SpriteComponent*>();

	//this is test code
	const char* resource = "Resources/Player.PNG";
	if (!LoadResource(resource))
	{
		return false;
	}
	////////////////////////////
	return true;
}

void Graphics::CleanGraphics()
{
	ClearDrawList();
	
	if (spDrawList != nullptr)
	{
		delete spDrawList;
	}

	//Clean up Graphics and clear any memory allocated for surfaces and textures
	if (spBitmapTexture != nullptr)
	{
		SDL_DestroyTexture(spBitmapTexture);
	}

	if (spRenderer != nullptr)
	{
		SDL_DestroyRenderer(spRenderer);
	}
}

void Graphics::Render()
{
	SDL_RenderClear(spRenderer);

	for (SpriteComponent *component : *spDrawList)
	{
		if (component != nullptr)
		{
			SDL_RenderCopy(spRenderer, component->m_Sprite->pBitmapTexture, 
				&component->m_Sprite->SpriteSrcRect, &component->m_Sprite->SpriteDestRect);
		}
	}

	SDL_RenderPresent(spRenderer);
}

SDL_Texture *Graphics::LoadResource(const char* resource)
{
	spBitmapSurface = IMG_Load(resource);
	if (!spBitmapSurface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load Image resource: %s. Error: %s", resource, SDL_GetError());
		return false;
	}

	//this is probably slow. I should probably put a bunch of sprites on here before blitting
	SDL_Texture *texture = SDL_CreateTextureFromSurface(spRenderer, spBitmapSurface);
	if (!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to Blit SDL Surface to Texture during Draw Step. Error: %s", SDL_GetError());
		return texture;
	}
	SDL_FreeSurface(spBitmapSurface);

	return texture;
}

void Graphics::ClearDrawList()
{
	if (spDrawList != nullptr)
	{
		spDrawList->clear();
	}
}

void Graphics::RegisterSpriteToDraw(SpriteComponent *const spriteComp)
{
	spDrawList->push_back(spriteComp);
	spDrawList->unique(); //clear any dupes
}

void Graphics::RemoveSpriteFromDrawList(SpriteComponent *const spriteComp)
{
	spDrawList->remove(spriteComp);
}

void Graphics::SortByZOrder()
{
	spDrawList->sort([](const SpriteComponent *one, const SpriteComponent *two)
	{
		return (one->m_Sprite->zOrder >= two->m_Sprite->zOrder);
	});
}

void Graphics::SetSrcRectFromTexture(SDL_Texture *const texture, SDL_Rect &rect)
{
	int w, h;
	if (!SDL_QueryTexture(texture, NULL, NULL, &w, &h))
	{
		rect.x = rect.y = 0;
		rect.w = w;
		rect.h = h;
	}
}