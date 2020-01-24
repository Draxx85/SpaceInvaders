#include "TextComponent.h"

TextComponent::TextComponent()
	:DisplayText("")
{
	m_FontColor.a = 255;
	m_FontColor.r = 255;
	m_FontColor.g = 255;
	m_FontColor.b = 255;
}

TextComponent::TextComponent(Entity &parent) : SpriteComponent(parent)
{
	m_FontColor.a = 255;
	m_FontColor.r = 255;
	m_FontColor.g = 255;
	m_FontColor.b = 255;
	UpdateText();

}

TextComponent::TextComponent(Entity &parent, const char *str) : SpriteComponent(parent)
{
	m_FontColor.a = 255;
	m_FontColor.r = 255;
	m_FontColor.g = 255;
	m_FontColor.b = 255;
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
}