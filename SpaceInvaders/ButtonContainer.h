#pragma once
#include "Button.h"
class ButtonContainer
{
public:
	ButtonContainer();
	ButtonContainer(SDL_Rect buttonSpace);
	~ButtonContainer();

	void AddButtonToList(Button *button);
	void ClearButtonList();

	ButtonContainer operator++();
	ButtonContainer operator--();

	ButtonContainer operator++(int);
	ButtonContainer operator--(int);

	void SetButtonSpacing(int horizontal, int vertical);
private:
	SDL_Rect m_Container;
	std::vector<Button*> *m_ButtonList;
	std::vector<Button*>::iterator m_Selected;

	int m_HorizontalSpacing = 0;
	int m_VerticalSpacing = 25;
};