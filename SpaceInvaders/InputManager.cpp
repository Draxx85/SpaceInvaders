#include "InputManager.h"

InputManager::InputManager()
{
}

void InputManager::ListenForKeyPress(SDL_Event &e)
{
	switch (e.type)
	{
		case SDL_KEYDOWN:
			//do key down
			break;
		case SDL_KEYUP:
			//do key release
			break;
		default:
			//ignore and return;
			return;
	}
}
