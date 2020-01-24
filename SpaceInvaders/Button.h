#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include "TextComponent.h"

enum EButtonStates
{
	Disabled = 0,
	Enabled = 1,
	Highlighted = 2,
};

class Button : public Entity
{
public:
	Button();
	virtual ~Button();

	StateMachine *m_ButtonState;
	
	void(*Activate)(float deltaTime);
	bool IsHighlighted();
	bool m_IsHighlighted = false;
	void SetHighlighted(bool isSelected);

	void AddComponent(Component *component) override;
private:
	TextComponent *m_TextComponent;

};