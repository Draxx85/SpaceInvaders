#include "Player.h"

Player::Player()
{
	SpriteComponent *playerSprite = 
		new SpriteComponent(*this, Graphics::LoadResource("Resources/SpaceInvaders-Sprite.png"));
	
	AddComponent(playerSprite);
	playerSprite->m_Sprite->SpriteSrcRect.h = playerSprite->m_Sprite->SpriteSrcRect.w = 128;
	playerSprite->m_Sprite->SpriteSrcRect.x = playerSprite->m_Sprite->SpriteSrcRect.y = 0;
	playerSprite->m_Sprite->SpriteDestRect.h = playerSprite->m_Sprite->SpriteDestRect.w = 128;

	playerSprite->SetVisible(true);
	BindKeys();
	SetPosition(SVector2D(Graphics::sWindowWidth / 2,
		(Graphics::sWindowHeight - (Graphics::sWindowHeight / 3.5))));

	UpdateManager::RegisterUpdate(this);
	UpdateManager::RegisterTimedUpdate(this);
}

Player::~Player()
{
	UpdateManager::ClearUpdate(this);
	UpdateManager::ClearTimedUpdate(this);
}

void Player::BindKeys()
{
	KeyBind left;
	KeyBind right;
	KeyBind shoot;

	left.m_Command = this;
	right.m_Command = this;
	shoot.m_Command = this;

	left.m_InputAction = Left;
	right.m_InputAction = Right;
	shoot.m_InputAction = Shoot;
	InputManager::RegisterKeyToAction(SDLK_RIGHT, right);
	InputManager::RegisterKeyToAction(SDLK_LEFT, left);
	InputManager::RegisterKeyToAction(SDLK_SPACE, shoot);
	
	//alternate key binds
	InputManager::RegisterKeyToAction(SDLK_a, left);
	InputManager::RegisterKeyToAction(SDLK_d, right);
	InputManager::RegisterKeyToAction(SDLK_SPACE, shoot);
}

void Player::UnBindKeys()
{
	InputManager::ClearKeyBinds();
}

void Player::Update(float deltaTime)
{
	
}

void Player::TimedUpdate(float deltaTime)
{
	Move(m_CurrentSpeed * deltaTime, 0);
}

void Player::Execute(void *params)
{
	//This is bad...
	KeyBind *action = static_cast<KeyBind*>(params);
	if (action != nullptr)
	{
		if (action->m_KeyState == KeyDown)
		{
			switch (action->m_InputAction)
			{
				case Left:
					m_CurrentSpeed = -m_kMaxSpeed;
					break;
				case Right:
					m_CurrentSpeed = m_kMaxSpeed;
					break;
				case Shoot:
					Fire();
					SDL_Log("Shooting");
					break;
				default:
					break;
			}
		}
		else if (action->m_KeyState == KeyUp)
		{
			switch (action->m_InputAction)
			{
				case Left:
				case Right:
					m_CurrentSpeed = 0;
					break;
				case Shoot:
					
					break;
				default:
					break;
			}
		}
	}
}
