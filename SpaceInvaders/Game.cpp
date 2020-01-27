#include "Game.h"

Game::Game()
	:m_SSLarian(new Entity())
{
	BuildArena();
	AddPlayer();
	CreateLevel();
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
	m_SSLarian->SetScale(0.75f, 0.75f);
	pos.x = (float)Graphics::sWindowWidth / 2 - (spriteComp->m_Sprite->SpriteDestRect.w / 2);
	pos.y = (float)Graphics::sWindowHeight - (spriteComp->m_Sprite->SpriteDestRect.h / 4);
	
	m_SSLarian->SetPosition(pos);
}

void Game::AddPlayer()
{
	m_Player = new Player();
}

void Game::CreateLevel()
{
	m_EnemyGrid = new EnemyGrid();
	m_EnemyGrid->PopulateEnemyGrid(1);
}
