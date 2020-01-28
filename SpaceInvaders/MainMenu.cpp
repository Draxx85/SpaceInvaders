#include "MainMenu.h"

MainMenu::MainMenu()
	:m_GameTitle(new Entity()), m_Buttons(new ButtonContainer),
	m_StartGame(new Button()), m_Leaderboards(new Button()), m_Exit(new Button())
{
	InitLogo();
	AddButtons();
	RegisterKeybinds();
	AudioManager::LoadMusicResource("Resources/menu.ogg");
	AudioManager::PlayMusic();
}

MainMenu::~MainMenu()
{
	InputManager::ClearKeyBinds();
	AudioManager::ClearMusic();

	delete m_GameTitle;

	//Main menu owns the buttons so should delete them
	delete m_StartGame;
	delete m_Leaderboards;
	delete m_Exit;

	delete m_Buttons;

	m_GameTitle		= nullptr;
	m_StartGame		= nullptr;
	m_Leaderboards	= nullptr;
	m_Exit			= nullptr;
	m_Buttons		= nullptr;
}

void MainMenu::Execute(void *params)
{
	KeyBind *action = static_cast<KeyBind*>(params);
	if (action != nullptr)
	{
		if (action->m_KeyState == KeyUp)
		{
			switch (action->m_InputAction)
			{
				case Up:
					--(*m_Buttons);
					break;
				case Down:
					++(*m_Buttons);
					break;
				case Select:
					m_Buttons->GetSelectedButton()->Activate(0.0f);
					break;
				default:
					break;
			}
		}
	}
}

void MainMenu::InitLogo()
{
	//Create The Logo and place it on Screen
	SpriteComponent *sprite = new SpriteComponent(Graphics::LoadResource("Resources/logo.png"));
	m_GameTitle->AddComponent(sprite);
	//Set it to visible
	sprite->SetVisible(true);

	int x = (Graphics::sWindowWidth / 2) - (sprite->m_Sprite->SpriteDestRect.w / 2);
	m_GameTitle->SetPosition(SVector2D(x, 0));
}

void MainMenu::AddButtons()
{
	InitStartGame();
//	InitLeaderboard(); // Didnt have time to add this
	InitExit();

	m_Buttons->AddButtonToList(m_StartGame);
//	m_Buttons->AddButtonToList(m_Leaderboards);
	m_Buttons->AddButtonToList(m_Exit);

	int x = (Graphics::sWindowWidth / 2) - (m_Buttons->GetContainerWidth() / 2);
	int y = Graphics::sWindowHeight / 2;
	m_Buttons->SetPosition(x, y);
}

void MainMenu::InitStartGame()
{
	TextComponent *textComp = new TextComponent(*m_StartGame, "Start Game");
	m_StartGame->AddComponent(textComp);
	m_StartGame->Activate = [](float deltaTime) { GameManager::StartGame();};
	textComp->SetVisible(true);
	m_StartGame->AddComponent(new SoundComponent(AudioManager::LoadSFXResource("Resources/MenuMove.wav")));
	m_StartGame->AddComponent(new SoundComponent(AudioManager::LoadSFXResource("Resources/Select.wav")));
}

void MainMenu::InitLeaderboard()
{
	TextComponent *textComp = new TextComponent(*m_Leaderboards, "Leaderboards");
	m_Leaderboards->AddComponent(textComp);
	m_Leaderboards->AddComponent(new SoundComponent(AudioManager::LoadSFXResource("Resources/MenuMove.wav")));
	m_Leaderboards->AddComponent(new SoundComponent(AudioManager::LoadSFXResource("Resources/Select.wav")));
	m_Leaderboards->Activate = [](float deltaTime) { return; };
	textComp->SetVisible(true);
}

void MainMenu::InitExit()
{
	TextComponent *textComp = new TextComponent(*m_Exit, "Exit");
	m_Exit->AddComponent(textComp);
	m_Exit->AddComponent(new SoundComponent(AudioManager::LoadSFXResource("Resources/MenuMove.wav")));
	m_Exit->AddComponent(new SoundComponent(AudioManager::LoadSFXResource("Resources/Select.wav")));
	m_Exit->Activate = [](float deltaTime)
	{
		SDL_Event sdlevent;
		sdlevent.type = SDL_QUIT;
		SDL_PushEvent(&sdlevent);
	};
	textComp->SetVisible(true);
}

void MainMenu::RegisterKeybinds()
{
	KeyBind up;
	up.m_Command = this;
	up.m_InputAction = Up;
	InputManager::RegisterKeyToAction(SDLK_UP, up);

	KeyBind down;
	down.m_Command = this;
	down.m_InputAction = Down;
	InputManager::RegisterKeyToAction(SDLK_DOWN, down);

	KeyBind select;
	select.m_Command = this;
	select.m_InputAction = Select;
	InputManager::RegisterKeyToAction(SDLK_RETURN, select);

	InputManager::RegisterKeyToAction(SDLK_w, up);
	InputManager::RegisterKeyToAction(SDLK_s, down);
	InputManager::RegisterKeyToAction(SDLK_SPACE, select);
}
