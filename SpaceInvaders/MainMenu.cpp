#include "MainMenu.h"

MainMenu::MainMenu()
	:m_GameTitle(new Entity()), m_StartGame(nullptr),
	m_Leaderboards(nullptr), m_Exit(nullptr)
{
	InitLogo();
	InitStartGame();
	InitLeaderboard();
	InitExit();
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
	m_StartGame = new Button();
	TextComponent *textComp = new TextComponent(*m_StartGame, "Start Game");
	m_StartGame->AddComponent(textComp);
	textComp->SetVisible(true);
	textComp->m_Sprite->m_MaxFrames = 1;
	textComp->SetDestRect(&textComp->m_Sprite->SpriteSrcRect);
	m_StartGame->SetPosition(SVector2D((1920 / 2) - (textComp->m_Sprite->SpriteDestRect.w / 2), 1080 /2));
	
}

void MainMenu::InitLeaderboard()
{
	m_Leaderboards = new Button();
	TextComponent *textComp = new TextComponent(*m_Leaderboards, "Leaderboards");
	m_Leaderboards->AddComponent(textComp);
	textComp->SetVisible(true);
	textComp->m_Sprite->m_MaxFrames = 1;
	textComp->SetDestRect(&textComp->m_Sprite->SpriteSrcRect);
	m_Leaderboards->SetPosition(SVector2D((1920 / 2) - (textComp->m_Sprite->SpriteDestRect.w / 2), (1080 / 2) + (textComp->m_Sprite->SpriteDestRect.h) * 1.25));
}

void MainMenu::InitExit()
{
	m_Exit = new Button();
	TextComponent *textComp = new TextComponent(*m_Exit, "Exit");
	m_Exit->AddComponent(textComp);
	textComp->SetVisible(true);
	textComp->m_Sprite->m_MaxFrames = 1;
	textComp->SetDestRect(&textComp->m_Sprite->SpriteSrcRect);
	m_Exit->SetPosition(SVector2D((1920 / 2) - (textComp->m_Sprite->SpriteDestRect.w / 2), (1080 / 2) + (textComp->m_Sprite->SpriteDestRect.h)*2.5));
}
