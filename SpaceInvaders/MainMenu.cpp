#include "MainMenu.h"

MainMenu::MainMenu()
	:m_GameTitle(new Entity()), m_StartGame(nullptr),
	m_Leaderboards(nullptr), m_Exit(nullptr)
{
	InitLogo();
	InitStartGame();
}

MainMenu::~MainMenu()
{
	delete m_GameTitle;
	delete m_StartGame;
	delete m_Leaderboards;
	delete m_Exit;

	m_GameTitle		= nullptr;
	m_StartGame		= nullptr;
	m_Leaderboards	= nullptr;
	m_Exit			= nullptr;
}

void MainMenu::InitLogo()
{
	//Test Init Code========================== CLEAN ME=========================================
	SpriteComponent *sprite = new SpriteComponent(Graphics::LoadResource("Resources/logo.png"));
	m_GameTitle->AddComponent(sprite);
	sprite->SetVisible(true);
	sprite->m_Sprite->m_MaxFrames = 1;
	sprite->SetDestRect(&sprite->m_Sprite->SpriteSrcRect);
	m_GameTitle->SetPosition(SVector2D((1920 / 2) - (sprite->m_Sprite->SpriteDestRect.w / 2), 0));
}

void MainMenu::InitStartGame()
{

}

void MainMenu::InitLeaderboard()
{
}

void MainMenu::InitExit()
{
}
