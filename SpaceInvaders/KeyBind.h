#pragma once
#include "Command.h"
#include "InputManager.h"

enum KeyPressState
{
	Inactive,
	KeyDown,
	KeyHeld,
	KeyUp,
};

enum EInputAction;

struct KeyBind
{
public:
	~KeyBind()
	{
		m_Command = nullptr;
	}
	Command *m_Command;
	EInputAction m_InputAction;
	KeyPressState m_KeyState = Inactive;
};