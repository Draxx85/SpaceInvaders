#pragma once
#include "Command.h"

enum KeyPressState
{
	Inactive,
	KeyDown,
	KeyHeld,
	KeyUp,
};

enum EInputAction
{
	Left,
	Right,
	Shoot,
	MegaShot,
	Menu,
	Up,
	Down,
	Select,
	Exit,
	Restart,
};

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