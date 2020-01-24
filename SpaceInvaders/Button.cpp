#include "Button.h"

Button::Button()
{
	m_ButtonState = new StateMachine();
	State *state = m_ButtonState->CreateState((int)Disabled, NULL);
	state = state->AddChildState(m_ButtonState->CreateState((int)Enabled, NULL));
	state->NextStateConditionFunc = this->CheckHighlightState; //TODO: FIX ME
	state = state->AddChildState(m_ButtonState->CreateState((int)Highlighted, this->Activate));
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
