#include "TextComponent.h"

TextComponent::TextComponent()
	:DisplayText("")
{
	ResetColor();
}

TextComponent::TextComponent(Entity &parent) : SpriteComponent(parent)
{
	ResetColor();
	UpdateText();
}

TextComponent::TextComponent(Entity &parent, const char *str) : SpriteComponent(parent)
{
	ResetColor();
	SetText(str);
}


TextComponent::~TextComponent()
{
	SpriteComponent::~SpriteComponent();
}

void TextComponent::SetText(std::string text)
{
	DisplayText = text;
	UpdateText();
}

void TextComponent::SetFontColor(SDL_Color color)
{
	m_FontColor = color;
	UpdateText();
}

void TextComponent::SetTextAndFontColor(std::string text, SDL_Color color)
{
	DisplayText = text;
	m_FontColor = color;
	UpdateText();
}

void TextComponent::UpdateText()
{
	m_Sprite->FreeTexture();
	m_Sprite->pBitmapTexture = Graphics::LoadText(DisplayText.c_str(), m_FontColor);
	Graphics::SetSrcRectFromTexture(m_Sprite->pBitmapTexture, m_Sprite->SpriteSrcRect);
	SyncParentToComponent();
	//Match the destination rect to the src as default;
	SetDestRect(&m_Sprite->SpriteSrcRect);
}

void TextComponent::ResetColor()
{
	m_FontColor.a = 255;
	m_FontColor.r = 255;
	m_FontColor.g = 255;
	m_FontColor.b = 255;
}