#pragma once
#include "SDL_ttf.h"
#include <string>
#include "SpriteComponent.h"

class TextComponent : public SpriteComponent
{
public:
	TextComponent();
	TextComponent(Entity &parent);
	TextComponent(Entity &parent, const char *str);

	virtual ~TextComponent();

	void SetText(std::string text);
	void SetFontColor(SDL_Color color);
	void SetTextAndFontColor(std::string text, SDL_Color color);
	void ResetColor();
	void SetColor(int a, int r, int g, int b);
	void SetShadeColor(int a, int r, int g, int b);
	void UpdateText(bool shaded = false);

private:
	std::string DisplayText;
	SDL_Color m_FontColor;
	SDL_Color m_ShadeColor;
	
};