#include "Game.h"

Game::Game()
	:m_SSLarian(new Entity()), m_Background(new Entity())
{
	BuildArena();
	AddPlayer();
	CreateLevel();
	AudioManager::LoadMusicResource("Resources/game.ogg");
	AudioManager::PlayMusic();
}

Game::~Game()
{
	SAFE_DELETE(m_Background);
	SAFE_DELETE(m_SSLarian);
}

void Game::BuildArena()
{
	SVector2D pos;
	SpriteComponent *spriteComp = new SpriteComponent(Graphics::LoadResource("Resources/spaceimage.png"));
	m_Background->AddComponent(spriteComp);
	spriteComp->SetVisible(true);
	m_Background->SetScale(1.f, 1.f);

	m_Background->SetPosition(0.f,0.f);

	spriteComp = new SpriteComponent(Graphics::LoadResource("Resources/ShipHull.png"));
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
	m_EnemyGrid->PopulateEnemyGrid(3);
}
