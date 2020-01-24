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

	~TextComponent();

	void SetText(std::string text);
	void SetFontColor(SDL_Color color);
	void SetTextAndFontColor(std::string text, SDL_Color color);

private:
	std::string DisplayText;
	SDL_Color m_FontColor;
	void UpdateText();
};