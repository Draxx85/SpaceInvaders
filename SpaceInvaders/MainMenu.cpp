#include "MainMenu.h"

MainMenu::MainMenu()
	:m_GameTitle(new Entity()), m_Buttons(new ButtonContainer),
	m_StartGame(new Button()), m_Leaderboards(new Button()), m_Exit(new Button())
{
	InitLogo();
	AddButtons();
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
	//Create The Logo and place it on Screen
	SpriteComponent *sprite = new SpriteComponent(Graphics::LoadResource("Resources/logo.png"));
	m_GameTitle->AddComponent(sprite);
	//Set it to visible
	sprite->SetVisible(true);

	int x = (1920 / 2) - (sprite->m_Sprite->SpriteDestRect.w / 2);
	m_GameTitle->SetPosition(SVector2D(x, 0));
}

void MainMenu::AddButtons()
{
	InitStartGame();
	InitLeaderboard();
	InitExit();

	m_Buttons->AddButtonToList(m_StartGame);
	m_Buttons->AddButtonToList(m_Leaderboards);
	m_Buttons->AddButtonToList(m_Exit);

	int x = (Graphics::sWindowWidth / 2) - (m_Buttons->GetContainerWidth() / 2);
	int y = Graphics::sWindowHeight / 2;
	m_Buttons->SetPosition(x, y);
}

void MainMenu::InitStartGame()
{
	TextComponent *textComp = new TextComponent(*m_StartGame, "Start Game");
	m_StartGame->AddComponent(textComp);
	textComp->SetVisible(true);
}

void MainMenu::InitLeaderboard()
{
	TextComponent *textComp = new TextComponent(*m_Leaderboards, "Leaderboards");
	m_Leaderboards->AddComponent(textComp);
	textComp->SetVisible(true);
}

void MainMenu::InitExit()
{
	TextComponent *textComp = new TextComponent(*m_Exit, "Exit");
	m_Exit->AddComponent(textComp);
	textComp->SetVisible(true);
}
