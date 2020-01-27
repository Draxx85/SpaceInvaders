#include "Button.h"

Button::Button()
{
	m_ButtonState = new StateMachine();
	State *state = m_ButtonState->CreateState((int)Disabled, NULL);
	
	state = state->AddChildState(m_ButtonState->CreateState((int)Enabled, NULL));

	state = state->AddChildState(m_ButtonState->CreateState((int)Highlighted, this->Activate));
	
	state->AddChildState(state->GetParent());
}

Button::~Button()
{
	SAFE_DELETE(m_ButtonState);
	m_Highlight, m_Select, m_TextComponent = nullptr; //this should be handled by the Entity Destructor
	Activate = nullptr;
}

bool Button::IsHighlighted()
{
	return m_IsHighlighted;
}

void Button::SetHighlighted(bool isSelected)
{
	m_IsHighlighted = isSelected;
	if (m_TextComponent != nullptr)
	{
		m_TextComponent->UpdateText(isSelected);
	}
	if (isSelected && m_Highlight != nullptr)
	{
		m_Highlight->Play();
	}
	if (m_ButtonState->m_ActiveState != nullptr) //Make sure State Machine is running
	{
		m_ButtonState->m_ActiveState->IsNextStateReady = [] { return true; }; //Hack to make the state work properly :(
		
	}
}

void Button::PlaySelected()
{
	if (m_Select == nullptr)
	{
		m_Select->Play();
	}
}

void Button::AddComponent(Component *component)
{
	Entity::AddComponent(component);
	TextComponent *ptext = dynamic_cast<TextComponent*>(component);
	if (ptext != nullptr)
	{
		m_TextComponent = ptext;
	}
	SoundComponent *sound = dynamic_cast<SoundComponent*>(component); //Super hacky but this is to save time... :(
	if (sound != nullptr)
	{
		if (m_Highlight == nullptr)
		{
			m_Highlight = sound;
		}
		else
		{
			m_Select = sound;
		}
	} 	
}

void Button::UpdateTexture()
{
	if (m_TextComponent != nullptr)
	{
		m_TextComponent->UpdateText(IsHighlighted());
	}
}