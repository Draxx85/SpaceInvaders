#pragma once
#include "Entity.h"
#include "SpriteComponent.h"
#include "Button.h"
#include "TextComponent.h"
#include "ButtonContainer.h"
#include "InputManager.h"
#include "GameManager.h"

class MainMenu : Command
{
public:
	MainMenu();
	~MainMenu();

	Entity *m_GameTitle;
	ButtonContainer *m_Buttons;

	void Execute(void* params);
private:
	void InitLogo();
	void AddButtons();
	void InitStartGame();
	void InitLeaderboard();
	void InitExit();
	void RegisterKeybinds();

	Button *m_StartGame;
	Button *m_Leaderboards;
	Button *m_Exit;
};