#pragma once
#include "Entity.h"
#include "SpriteComponent.h"
#include "Button.h"
#include "TextComponent.h"
#include "ButtonContainer.h"

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	Entity *m_GameTitle;
	ButtonContainer *m_Buttons;
private:
	void InitLogo();
	void AddButtons();
	void InitStartGame();
	void InitLeaderboard();
	void InitExit();

	Button *m_StartGame;
	Button *m_Leaderboards;
	Button *m_Exit;
};