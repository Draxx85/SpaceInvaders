#pragma once
#include "Entity.h"
#include "SpriteComponent.h"
#include "Button.h"
#include "TextComponent.h"

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	Entity *m_GameTitle;
	Button *m_StartGame;
	Button *m_Leaderboards;
	Button *m_Exit;

private:
	void InitLogo();
	void InitStartGame();
	void InitLeaderboard();
	void InitExit();

};