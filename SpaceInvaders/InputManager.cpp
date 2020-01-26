#include "InputManager.h"

std::map<SDL_Keycode, KeyBind> *InputManager::sKeyBinds;
int InputManager::m_xAxis = 0;
int InputManager::m_yAxis = 0;
SDL_GameController *InputManager::sGameController = nullptr;

InputManager::InputManager()
{
}

void InputManager::Init()
{
	sKeyBinds = new std::map<SDL_Keycode, KeyBind>();

	int MaxJoysticks = SDL_NumJoysticks();

	sGameController = SDL_GameControllerOpen(0);
}

void InputManager::ListenForKeyPress(SDL_Event &e)
{
	std::map<SDL_Keycode, KeyBind>::iterator key = sKeyBinds->find(e.key.keysym.sym);
	if (key != sKeyBinds->end())
	{
		switch (e.type)
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				(*key).second.m_KeyState = CalcKeyState(e.type);
				(*key).second.m_Command->Execute(&(*key).second);
				break;
			default:
				//ignore and return;
				return;
		}
	}
}

void InputManager::CheckForControllerInput()
{
	if (sGameController != nullptr && SDL_GameControllerGetAttached(sGameController))
	{
		// NOTE: We have a controller with index ControllerIndex.
		bool Up = SDL_GameControllerGetButton(sGameController, SDL_CONTROLLER_BUTTON_DPAD_UP);
		bool Down = SDL_GameControllerGetButton(sGameController, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
		bool Left = SDL_GameControllerGetButton(sGameController, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
		bool Right = SDL_GameControllerGetButton(sGameController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		bool Start = SDL_GameControllerGetButton(sGameController, SDL_CONTROLLER_BUTTON_START);
		bool Back = SDL_GameControllerGetButton(sGameController, SDL_CONTROLLER_BUTTON_BACK);

		bool AButton = SDL_GameControllerGetButton(sGameController, SDL_CONTROLLER_BUTTON_A);

		Sint16 StickX = SDL_GameControllerGetAxis(sGameController, SDL_CONTROLLER_AXIS_LEFTX);
		Sint16 StickY = SDL_GameControllerGetAxis(sGameController, SDL_CONTROLLER_AXIS_LEFTY);
	}
	else
	{
		// TODO: This controller is note plugged in.
	}
}
KeyPressState InputManager::CalcKeyState(Uint32 type)
{
	switch (type)
	{
		case SDL_KEYDOWN:
			return KeyDown;
		case SDL_KEYUP:
			return KeyUp;
	}
	return Inactive;
}

void InputManager::RegisterKeyToAction(SDL_Keycode key, KeyBind bind)
{
	(*sKeyBinds)[key] = bind;
}

void InputManager::ClearKeyBinds()
{
	sKeyBinds->clear();
}

void InputManager::CleanUp()
{
	SDL_GameControllerClose(0);
	ClearKeyBinds();
	SAFE_DELETE(sKeyBinds);
}
