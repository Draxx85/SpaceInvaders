#include "Graphics.h"

SDL_Surface *Graphics::spBitmapSurface = nullptr;
SDL_Renderer *Graphics::spRenderer = nullptr;
std::list<SpriteComponent *> *Graphics::spDrawList = nullptr;
TTF_Font *Graphics::m_Font = nullptr;

SDL_Texture *Graphics::spActortexture = nullptr;

int Graphics::sWindowWidth = 1280;
int Graphics::sWindowHeight = 960;
bool Graphics::InitGraphics()
{
	
	spRenderer = SDL_CreateRenderer(Engine::GetWindow(), -1, SDL_RENDERER_ACCELERATED);
	
	if (spRenderer == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize Renderer. Error: %s", SDL_GetError());
	}

	spDrawList = new std::list<SpriteComponent*>();
	
	if (TTF_Init() == -1)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL_ttf! Error: %s\n", TTF_GetError());
	}

	m_Font = TTF_OpenFont("Resources/Pixeled.ttf", 32);
	if (m_Font == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	//Load this into memory and keep a pointer to it fpr actors
	spActortexture = Graphics::LoadResource("Resources/SpaceInvaders-Sprite.png");

	return true;
}

void Graphics::CleanGraphics()
{
	ClearDrawList();
	
	SAFE_DELETE(spDrawList);

	//Clean Up font
	TTF_CloseFont(m_Font);
	m_Font = nullptr;

	if (spActortexture != nullptr)
	{
		SDL_DestroyTexture(spActortexture);
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
		//	SDL_RenderDrawRect(Graphics::spRenderer, &component->m_Sprite->SpriteDestRect);
		}
	}

	SDL_RenderPresent(spRenderer);
}

SDL_Texture *Graphics::LoadActorResource()
{
	return spActortexture;
}

//TODO: Keep References of resources with links to texture for asset sharing
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

SDL_Texture *Graphics::LoadTextSolid(const char * text, SDL_Color color)
{
	return LoadText(TTF_RenderText_Solid(m_Font, text, color));	
}

SDL_Texture *Graphics::LoadTextShaded(const char *text, SDL_Color color, SDL_Color shadedColor)
{
	return LoadText(TTF_RenderText_Shaded(m_Font, text, color, shadedColor));
}

SDL_Texture *Graphics::LoadText(SDL_Surface* pSurface)
{
	SDL_Texture *pTexture = nullptr;
	if (pSurface == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not render text to surface using SDL_ttf. Error: %s", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		pTexture = SDL_CreateTextureFromSurface(spRenderer, pSurface);
		if (pTexture == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from text! Error: %s", SDL_GetError());
		}

		//Get rid of old surface
		SDL_FreeSurface(pSurface);
	}

	//Return success
	return pTexture;
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
