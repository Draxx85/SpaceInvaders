#include "Game.h"

Game::Game()
	:m_SSLarian(new Entity())
{
	BuildArena();
	AddPlayer();
}

Game::~Game()
{
}

void Game::BuildArena()
{
	SVector2D pos;
	SpriteComponent *spriteComp = new SpriteComponent(Graphics::LoadResource("Resources/ShipHull.png"));
	m_SSLarian->AddComponent(spriteComp);
	spriteComp->SetVisible(true);
	
	pos.x = (float)Graphics::sWindowWidth / 2 - (spriteComp->m_Sprite->SpriteSrcRect.w / 2);
	pos.y = (float)Graphics::sWindowHeight - (spriteComp->m_Sprite->SpriteSrcRect.h / 3);
	
	m_SSLarian->SetPosition(pos);
}

void Game::AddPlayer()
{
	m_Player = new Player();
}
