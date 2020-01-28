#include "Game.h"
#include <sstream>
Game::Game()
	:m_SSLarian(new Entity()), m_Background(new Entity()), m_Floaters(new std::vector<Floater*>())
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

void Game::StartGame(int level)
{
	m_EnemyGrid->PopulateEnemyGrid(level);
	m_Player->BindKeys();
	m_Player->ResetPlayer();
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
		StartGame(m_levelIndex++);
		m_RoundCountDown = 0;
	}
}

void Game::BetweenRoundCleanUp()
{
	m_Player->UnBindKeys();
	m_Floaters->clear();
	m_FinishedCleaning = true;
	m_Player->ResetPlayer();
	SAFE_DELETE(m_ShipBlocks[0]);
	SAFE_DELETE(m_ShipBlocks[1]);
	SAFE_DELETE(m_ShipBlocks[2]);
}

void Game::Update()
{
	
	if (m_EnemyGrid->m_EnemyCount <= 0)
	{
		m_GameActive = false;
		m_EnemyGrid->ClearGrid();
	}
}

void Game::CreateRoundIntermission()
{
	m_FinishedCleaning = false;
	m_GameReadyToStart = false;
	std::stringstream ss;
	ss << "Round " << m_levelIndex;
	SVector2D vec = SVector2D(Graphics::sWindowWidth / 2, Graphics::sWindowHeight / 2);
	Floater *RoundMsg = new Floater(ss.str().c_str() , vec, 2.f);

	m_ShipBlocks[0] = new ShipBlock(SVector2D(150, 600));
	m_ShipBlocks[1] = new ShipBlock(SVector2D(500, 600));
	m_ShipBlocks[2] = new ShipBlock(SVector2D(850, 600));
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
	m_EnemyGrid = new EnemyGrid();
	pos.x = 500;
	pos.y = 250;

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
}

void Game::UpdateScore(int value)
{
	m_Score += value;
	std::stringstream ss;
	ss << "Score : " << m_Score;
	m_ScoreEntity->UpdateFloater(ss.str().c_str(), m_Color);
	m_ScoreEntity->SetScale(0.5f, 0.5f);
}

void Game::AddFloater(SVector2D pos, int value)
{
	Floater *floater = new Floater(value, pos, 0.75f);
	floater->SetScale(0.5f, 0.5f);
}


