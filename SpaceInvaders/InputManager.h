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
	//Making this non static so that I can support multiple inputs and players
	InputManager();
	void ListenForKeyPress(SDL_Event &e);

};