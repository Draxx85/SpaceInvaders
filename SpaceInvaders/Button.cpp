#include "Button.h"

Button::Button()
{
	m_ButtonState = new StateMachine();
	State *state = m_ButtonState->CreateState((int)Disabled, NULL);
	
	state = state->AddChildState(m_ButtonState->CreateState((int)Enabled, NULL));
	//state->IsNextStateReady = std::bind(&Button::IsHighlighted, this);

	state = state->AddChildState(m_ButtonState->CreateState((int)Highlighted, this->Activate));
	//state->IsNextStateReady = std::bind(&Button::IsHighlighted, this);
	
	state->AddChildState(state->GetParent());
}

Button::~Button()
{
	delete m_ButtonState;
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
	if (m_ButtonState->m_ActiveState != nullptr) //Make sure State Machine is running
	{
		m_ButtonState->m_ActiveState->IsNextStateReady = [] { return true; }; //Hack to make the state work properly :(
	}
}

void Button::AddComponent(Component *component)
{
	Entity::AddComponent(component);
	m_TextComponent = dynamic_cast<TextComponent*>(component);
}

void Button::UpdateTexture()
{
	if (m_TextComponent != nullptr)
	{
		m_TextComponent->UpdateText(IsHighlighted());
	}
}