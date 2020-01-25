#pragma once
#include "SDL.h"

enum EInputActions
{
	Left,
	Right,
	Shoot,
	MegaShot,
};

class InputManager
{
public:
	static void ListenForKeyPress(SDL_Event &e);

private:
	InputManager();
};