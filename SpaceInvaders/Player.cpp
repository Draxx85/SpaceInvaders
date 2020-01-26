#include "Player.h"

Player::Player()
{
	SpriteComponent *playerSprite = 
		new SpriteComponent(*this, Graphics::LoadResource("Resources/SpaceInvaders-Sprite.png"));
	
	AddComponent(playerSprite);
	playerSprite->m_Sprite->SpriteSrcRect.h = playerSprite->m_Sprite->SpriteSrcRect.w = Graphics::skSpriteSheetWidth;
	playerSprite->m_Sprite->SpriteSrcRect.x = playerSprite->m_Sprite->SpriteSrcRect.y = 0;
	playerSprite->m_Sprite->SpriteDestRect.h = playerSprite->m_Sprite->SpriteDestRect.w = Graphics::skSpriteSheetWidth;

	playerSprite->SetVisible(true);
	BindKeys();
	SetPosition(SVector2D(Graphics::sWindowWidth / 2.f,
		(Graphics::sWindowHeight - (Graphics::sWindowHeight / 3.5f))));

	UpdateManager::RegisterUpdate(this);
	UpdateManager::RegisterTimedUpdate(this);
	m_AccelRatePerSec = kMaxSpeed / kTimeToMaxSpeed;
	m_TargetSpeed = 0.f;

	m_MaxProjectiles = 10;
	LoadProjectiles(-1, Blue);
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

void Player::Fire()
{
	for (std::vector<Projectile*>::iterator iter = m_ProjectilePool->begin();
		iter != m_ProjectilePool->end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			if (!(*iter)->IsActive())
			{
				(*iter)->Spawn();
				break;
			}
		}
	}
}

void Player::TimedUpdate(float deltaTime)
{
	if (m_TargetSpeed - kSpeedTolerance <= m_Velocity 
		&& m_Velocity <= m_TargetSpeed + kSpeedTolerance)
	{
		m_Velocity = m_TargetSpeed;
	}
	else if (m_Velocity < m_TargetSpeed)
	{
		m_Velocity += m_AccelRatePerSec * deltaTime;
	}
	else 
	{
		m_Velocity -= m_AccelRatePerSec * deltaTime;
	}
	Move(m_Velocity, 0);
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
					m_TargetSpeed = -kMaxSpeed;
					break;
				case Right:
					m_TargetSpeed = kMaxSpeed;
					break;
				case Shoot:
					Fire();
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
					m_TargetSpeed = 0;
					break;
				case Shoot:
					
					break;
				default:
					break;
			}
		}
	}
}
