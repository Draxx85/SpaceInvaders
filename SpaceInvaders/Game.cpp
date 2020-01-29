#include "Game.h"
#include <sstream>
#include "GameManager.h"

Game::Game()
	:m_SSLarian(new Entity()), m_Background(new Entity()), m_Floaters(new std::vector<Floater*>()), 
	m_Boss(new Boss())
{
	BuildArena();
	AudioManager::LoadMusicResource("Resources/game.ogg");
	AudioManager::PlayMusic();

	m_Color.a = 255;
	m_Color.b = 255;
	m_Color.g = 255;
	m_Color.r = 255;
	BuildUI();
	m_EnemyGrid->m_Game = this;
}

Game::~Game()
{
	SAFE_DELETE(m_Background);
	SAFE_DELETE(m_SSLarian);
}

void Game::StartGame()
{
	m_EnemyGrid->EnableGrid();
	m_Player->ResetPlayer();
	m_Player->BindKeys();
	m_SpawnedBossThisRound = false;
}

void Game::InitializeRoundLoop(float deltaTime)
{
	if (m_RoundCountDown < kRoundTime)
	{
		m_RoundCountDown += deltaTime;
	}
	else
	{
		m_GameReadyToStart = true;
		m_GameActive = true;
		StartGame();
		m_RoundCountDown = 0;
		m_BossCountDown = rand() % 10;
	}
}

void Game::BetweenRoundCleanUp()
{
	m_Player->UnBindKeys();
	m_Floaters->clear();
	m_FinishedCleaning = true;
	m_Player->ResetPlayer();
	m_ShipBlocks[0]->ResetBlocks();
	m_ShipBlocks[1]->ResetBlocks();
	m_ShipBlocks[2]->ResetBlocks();
}

void Game::Update(float update)
{
	m_BossCountDown -= update;
	if (m_BossCountDown <= 0 && !m_SpawnedBossThisRound)
	{
		m_Boss->Activate();
		m_SpawnedBossThisRound = true;
	}
	
	if (m_EnemyGrid->m_EnemyCount <= 0)
	{
		m_GameActive = false;
		m_EnemyGrid->ClearGrid();
	}
}

void Game::CreateRoundIntermission()
{
	CreateLevel();
	m_FinishedCleaning = false;
	m_GameReadyToStart = false;
	std::stringstream ss;
	ss << "Round " << m_levelIndex;
	SVector2D vec = SVector2D(Graphics::sWindowWidth / 2, Graphics::sWindowHeight / 2);
	Floater *RoundMsg = new Floater(ss.str().c_str() , vec, 2.f);
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

	m_EnemyGrid = new EnemyGrid();

	m_ShipBlocks[0] = new ShipBlock(SVector2D(50, 650));
	m_ShipBlocks[1] = new ShipBlock(SVector2D(500, 650));
	m_ShipBlocks[2] = new ShipBlock(SVector2D(950, 650));

	AddPlayer();
}

void Game::AddPlayer()
{
	m_Player = new Player();
}

void Game::CreateLevel()
{
	m_EnemyGrid->PopulateEnemyGrid(m_levelIndex);
	++m_levelIndex;
}

void Game::BuildUI()
{
	std::stringstream ss;
	ss << "Score : " << m_Score;
	m_ScoreEntity = new Floater(ss.str().c_str(), SVector2D(150, 30), -1);
	m_ScoreEntity->SetScale(0.5f, 0.5f);

	ss.clear();
	ss << "Lives: " << m_Player->health;
	m_PlayerStatusEntity = new Floater(ss.str().c_str(), SVector2D(Graphics::sWindowWidth - 200, 30), -1);
	m_PlayerStatusEntity->SetScale(0.5f, 0.5f);
}

void Game::UpdateScore(int value)
{
	m_Score += value;
	std::stringstream ss;
	ss << "Score : " << m_Score;
	m_ScoreEntity->UpdateFloater(ss.str().c_str(), m_Color);
	m_ScoreEntity->SetScale(0.5f, 0.5f);
}

void Game::UpdateHealth()
{
	std::stringstream ss;
	ss << "Lives : " << m_Player->health;
	m_PlayerStatusEntity->UpdateFloater(ss.str().c_str(), m_Color);
	m_PlayerStatusEntity->SetScale(0.5f, 0.5f);
}

void Game::AddFloater(SVector2D pos, int value)
{
	Floater *floater = new Floater(value, pos, 0.75f);
	floater->SetScale(0.5f, 0.5f);
}

void Game::GameOver()
{
	SVector2D pos;
	pos.x = ((float)Graphics::sWindowWidth / 2) - 64;
	pos.y = ((float)Graphics::sWindowHeight /2)- 64;
	Floater *floater = new Floater("Hard Luck!", pos, -1);
	GameManager::Pause();
}


