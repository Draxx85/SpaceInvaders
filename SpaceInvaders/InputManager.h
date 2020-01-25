#pragma once
#include "SDL.h"
#include "Command.h"
#include "KeyBind.h"
#include <map>

enum EInputAction
{
	Left,
	Right,
	Shoot,
	MegaShot,
	//Menu
	Up,
	Down,
	Select,
};

class InputManager
{
public:
	static void Init();
	static void ListenForKeyPress(SDL_Event &e);
	static KeyPressState CalcKeyState(Uint32 type);
	static void RegisterKeyToAction(SDL_Keycode key, KeyBind bind);
private:
	InputManager();
	static std::map<SDL_Keycode, KeyBind> *m_KeyBinds;

};