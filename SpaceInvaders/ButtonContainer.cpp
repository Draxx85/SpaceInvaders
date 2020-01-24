#include "ButtonContainer.h"

ButtonContainer::ButtonContainer() 
	:m_ButtonList(new std::vector<Button*>()), m_Selected(m_ButtonList->begin())
{
	
}

ButtonContainer::ButtonContainer(SDL_Rect buttonSpace)
	: m_ButtonList(new std::vector<Button*>()), m_Selected(m_ButtonList->begin())
{
	m_Container = buttonSpace;
}
ButtonContainer::~ButtonContainer()
{
	m_Selected = m_ButtonList->begin();
	while (m_Selected != m_ButtonList->end())
	{
		delete *m_Selected;
		++m_Selected;
	}
	ClearButtonList();
	delete m_ButtonList;
}

void ButtonContainer::AddButtonToList(Button *button)
{
	m_ButtonList->push_back(button);
}

void ButtonContainer::ClearButtonList()
{
	m_ButtonList->clear();
}

ButtonContainer ButtonContainer::operator++()
{
	if (m_Selected != m_ButtonList->end())
	{
		++m_Selected;
	}
	else //wrap around
	{
		m_Selected = m_ButtonList->begin();
	}
	return *this;
}

ButtonContainer ButtonContainer::operator--()
{
	if (m_Selected != m_ButtonList->begin())
	{
		--m_Selected;
	}
	else //wrap around
	{
		m_Selected = m_ButtonList->end();
	}
	return *this;
}

ButtonContainer ButtonContainer::operator++(int)
{
	if (m_Selected != m_ButtonList->end())
	{
		++m_Selected;
	}
	else //wrap around
	{
		m_Selected = m_ButtonList->begin();
	}
	return *this;
}

ButtonContainer ButtonContainer::operator--(int)
{
	if (m_Selected != m_ButtonList->begin())
	{
		--m_Selected;
	}
	else //wrap around
	{
		m_Selected = m_ButtonList->end();
	}
	return *this;
}

void ButtonContainer::SetButtonSpacing(int horizontal, int vertical)
{
	for (Uint32 i = 0; i < m_ButtonList->size(); ++i)
	{
		Button* button = (*m_ButtonList)[i];
		if (button != nullptr)
		{
			int x = (m_Container.x*i) + (horizontal*i);
			int y = (m_Container.y*i) + (vertical*i);
			button->SetPosition(SVector2D(x, y));
		}
	}
	m_HorizontalSpacing = horizontal;
	m_VerticalSpacing = vertical;
}
