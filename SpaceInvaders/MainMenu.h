#pragma once
#include "Entity.h"
#include "SpriteComponent.h"
#include "Button.h"

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	Entity *m_GameTitle;
	Button *StartGame;
	Button *Leaderboards;
	Button *Exit;

private:
	void InitLogo();
	void InitStartGame();
	void InitLeaderboard();
	void InitExit();

};