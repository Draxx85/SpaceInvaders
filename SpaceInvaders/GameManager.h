#pragma once
#include "SDL.h"
#include "Component.h"
#include "Entity.h"
#include "SpriteComponent.h"

class GameManager
{
public:
	static void Init();
	static void StartGame();
private:
	GameManager();
};
