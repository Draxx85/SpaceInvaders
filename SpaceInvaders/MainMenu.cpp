#include "MainMenu.h"

MainMenu::MainMenu()
	:m_GameTitle(new Entity())
{
	//Test Init Code========================== CLEAN ME=========================================
	SpriteComponent *sprite = new SpriteComponent(Graphics::LoadResource("Resources/logo.png"));
	m_GameTitle->AddComponent(sprite);
	sprite->SetVisible(true);
	sprite->m_Sprite->m_MaxFrames = 1;
	sprite->SetDestRect(&sprite->m_Sprite->SpriteSrcRect);
	m_GameTitle->SetPosition(SVector2D((1920 / 2) - (sprite->m_Sprite->SpriteDestRect.w / 2),0));
	
}

MainMenu::~MainMenu()
{
}
