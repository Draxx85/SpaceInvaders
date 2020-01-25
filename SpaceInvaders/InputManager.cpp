#include "InputManager.h"

std::map<SDL_Keycode, KeyBind> *InputManager::m_KeyBinds;

InputManager::InputManager()
{
}

void InputManager::Init()
{
	m_KeyBinds = new std::map<SDL_Keycode, KeyBind>();
}

void InputManager::ListenForKeyPress(SDL_Event &e)
{
	std::map<SDL_Keycode, KeyBind>::iterator key = m_KeyBinds->find(e.key.keysym.sym);
	if (key != m_KeyBinds->end())
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
	(*m_KeyBinds)[key] = bind;
}

void InputManager::ClearKeyBinds()
{
	m_KeyBinds->clear();
}
