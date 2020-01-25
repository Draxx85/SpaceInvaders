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

void TextComponent::UpdateText(bool shaded)
{
	m_Sprite->FreeTexture();
	if (!shaded)
	{
		m_Sprite->pBitmapTexture = Graphics::LoadTextSolid(DisplayText.c_str(), m_FontColor);
	}
	else
	{
		m_Sprite->pBitmapTexture = Graphics::LoadTextShaded(DisplayText.c_str(), m_FontColor, m_ShadeColor);
	}
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

	m_ShadeColor.a = 255;
	m_ShadeColor.r = 255;
	m_ShadeColor.g = 0;
	m_ShadeColor.b = 0;
}

void TextComponent::SetColor(int a, int r, int g, int b)
{
	m_FontColor.a = a;
	m_FontColor.r = r;
	m_FontColor.g = g;
	m_FontColor.b = b;
}

void TextComponent::SetShadeColor(int a, int r, int g, int b)
{
	m_ShadeColor.a = a;
	m_ShadeColor.r = r;
	m_ShadeColor.g = g;
	m_ShadeColor.b = b;
}