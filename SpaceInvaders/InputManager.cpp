#include "InputManager.h"

std::map<SDL_Keycode, KeyBind> *InputManager::m_KeyBinds;
int InputManager::m_xAxis = 0;
int InputManager::m_yAxis = 0;

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

	if (e.type == SDL_JOYAXISMOTION)
	{
		//Motion on controller 0
		if (e.jaxis.which == 0)
		{
			//X axis motion
			if (e.jaxis.axis == 0)
			{
				//Left of dead zone
				if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					m_xAxis = -1;
				}
				//Right of dead zone
				else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					m_xAxis = 1;
					SDL_Log("JOYPAD");
				}
				else
				{
					m_xAxis = 0;
				}
			}
			//Y axis motion
			else if (e.jaxis.axis == 1)
			{
				//Below of dead zone
				if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					m_yAxis = -1;
				}
				//Above of dead zone
				else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					m_yAxis = 1;
				}
				else
				{
					m_yAxis = 0;
				}
			}
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
