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
	STransform *transform =  button->GetTransform();
	if (transform != nullptr)
	{
		m_ButtondWidth = transform->DestRect->w;
		m_BuittonHeight = transform->DestRect->h;
	}
	m_ButtonList->push_back(button);
	m_Selected = m_ButtonList->begin();
	RefreshDimensions(m_ButtonList->size());
	ResetSelection();
}

void ButtonContainer::ClearButtonList()
{
	m_ButtonList->clear();
}

ButtonContainer ButtonContainer::operator++()
{
	if (m_Selected != m_ButtonList->end())
	{
		(*m_Selected)->SetHighlighted(false);
		++m_Selected;
		(*m_Selected)->SetHighlighted(true);
	}
	else //wrap around
	{
		(*m_Selected)->SetHighlighted(false);
		m_Selected = m_ButtonList->begin();
		(*m_Selected)->SetHighlighted(true);
	}
	return *this;
}

ButtonContainer ButtonContainer::operator--()
{
	if (m_Selected != m_ButtonList->begin())
	{
		(*m_Selected)->SetHighlighted(false);
		--m_Selected;
		(*m_Selected)->SetHighlighted(true);
	}
	else //wrap around
	{
		(*m_Selected)->SetHighlighted(false);
		m_Selected = m_ButtonList->end();
		(*m_Selected)->SetHighlighted(true);
	}
	return *this;
}

ButtonContainer ButtonContainer::operator++(int)
{
	if (m_Selected != m_ButtonList->end())
	{
		(*m_Selected)->SetHighlighted(false);
		++m_Selected;
		(*m_Selected)->SetHighlighted(true);
	}
	else //wrap around
	{
		(*m_Selected)->SetHighlighted(false);
		m_Selected = m_ButtonList->begin();
		(*m_Selected)->SetHighlighted(true);
	}
	return *this;
}

ButtonContainer ButtonContainer::operator--(int)
{
	if (m_Selected != m_ButtonList->begin())
	{
		(*m_Selected)->SetHighlighted(false);
		--m_Selected;
		(*m_Selected)->SetHighlighted(true);
	}
	else //wrap around
	{
		(*m_Selected)->SetHighlighted(false);
		m_Selected = m_ButtonList->end();
		(*m_Selected)->SetHighlighted(true);
	}
	return *this;
}

void ButtonContainer::ResetButtonPositioning()
{
	int size = m_ButtonList->size();
	for (int i = 0; i < size; ++i)
	{
		Button* button = (*m_ButtonList)[i];
		if (button != nullptr)
		{
			int x = (m_Container.x); //Not going to implement horizontal alignment
			int y = (m_Container.y) + (m_BuittonHeight * i ) + (m_VerticalSpacing*i);
			button->SetPosition(SVector2D(x, y));
		}
	}
	RefreshDimensions(size);
}

void ButtonContainer::SetButtonSpacing(int horizontal, int vertical)
{
	int size = m_ButtonList->size();

	m_HorizontalSpacing = horizontal;
	m_VerticalSpacing = vertical;
	
	RefreshDimensions(size);
}

void ButtonContainer::SetPosition(int x, int y)
{
	m_Container.x = x;
	m_Container.y = y;
	ResetButtonPositioning();
}

int ButtonContainer::GetContainerWidth()
{
	return m_Container.w;
}
int ButtonContainer::GetContainerHeight()
{
	return m_Container.h;
}

inline void ButtonContainer::RefreshDimensions(int size)
{
	m_Container.h = (m_VerticalSpacing * size) + (m_BuittonHeight * size);
	m_Container.w = (m_HorizontalSpacing * size) + (m_ButtondWidth * size);
}

void ButtonContainer::ResetSelection()
{
	if ((*m_Selected) != nullptr)
	{
		(*m_Selected)->SetHighlighted(false);
	}
	if (m_ButtonList != nullptr)
	{
		m_Selected = m_ButtonList->begin();
		(*m_Selected)->SetHighlighted(true);
	}
}
