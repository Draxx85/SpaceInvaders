#include "Game.h"
#include <sstream>
Game::Game()
	:m_SSLarian(new Entity()), m_Background(new Entity()), m_Floaters(new std::vector<Floater*>())
{
	BuildArena();
	CreateLevel();
	BuildUI();
	AudioManager::LoadMusicResource("Resources/game.ogg");
	AudioManager::PlayMusic();


}

Game::~Game()
{
	SAFE_DELETE(m_Background);
	SAFE_DELETE(m_SSLarian);
	for (size_t i = 0; i < m_Floaters->size(); ++i)
	{
		SAFE_DELETE((*m_Floaters)[i]);
	}
	m_Floaters->clear();
	SAFE_DELETE(m_Floaters);
}

void Game::StartGame(int level)
{
	m_EnemyGrid->PopulateEnemyGrid(level);
	m_GameStarted = true;
}

void Game::InitializeRoundLoop(float deltaTime)
{
	if (m_RoundCountDown < kRoundTime)
	{
		m_RoundCountDown += deltaTime;
	}
	else
	{
		m_GameStarted = true;
		StartGame(m_levelIndex);
		m_Player->BindKeys();
		m_Player->ResetPlayer();
	}
}

void Game::ActiveCleanUp()
{
	
}

void Game::Update()
{
	if (m_GameStarted && m_EnemyGrid->m_EnemyCount <= 0)
	{
		m_GameStarted = false;
		m_EnemyGrid->ClearGrid();
		m_EnemyGrid->PopulateEnemyGrid(++m_levelIndex);
	}
}

void Game::CreateRoundIntermission()
{
	std::stringstream ss;
	ss << "Round " << m_levelIndex;
	SVector2D vec = SVector2D(Graphics::sWindowWidth / 2, Graphics::sWindowHeight / 2);
	Floater *RoundMsg = new Floater(ss.str().c_str() , vec, 2.f);
	m_Floaters->push_back(RoundMsg);
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
	AddPlayer();
}

void Game::AddPlayer()
{
	m_Player = new Player();
}

void Game::CreateLevel()
{
	m_EnemyGrid = new EnemyGrid();
	
	m_EnemyGrid->m_pGame = this;
}

void Game::BuildUI()
{
}


