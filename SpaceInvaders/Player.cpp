#include "Player.h"
#include "GameManager.h"

Player::Player()
	:m_KeyPressStack()
{
	SpriteComponent *playerSprite = 
		new SpriteComponent(*this, Graphics::LoadActorResource());
	
	//Setup the sprite
	AddComponent(playerSprite);
	playerSprite->m_Sprite->SpriteSrcRect.h = playerSprite->m_Sprite->SpriteSrcRect.w = Graphics::skSpriteSheetWidth;
	playerSprite->m_Sprite->SpriteSrcRect.x = playerSprite->m_Sprite->SpriteSrcRect.y = 0;
	playerSprite->m_Sprite->SpriteDestRect.h = playerSprite->m_Sprite->SpriteDestRect.w = Graphics::skSpriteSheetWidth;
	SetScale(0.75f, 0.75f);
	playerSprite->SetVisible(true);

	ResetPlayer(); //Reset his Position to the default starting position
	
	//Register Collision
	CollisionComponent *collider = new CollisionComponent(PlayerCollidables, *this);
	AddComponent(collider);
	collider->Register();
	
	m_ShootSound = new SoundComponent(AudioManager::LoadSFXResource("Resources/shoot.wav"));
	AddComponent(m_ShootSound);

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
	KeyBind pause;

	left.m_Command = this;
	right.m_Command = this;
	shoot.m_Command = this;
	pause.m_Command = this;

	left.m_InputAction = Left;
	right.m_InputAction = Right;
	shoot.m_InputAction = Shoot;
	pause.m_InputAction = Menu;

	InputManager::RegisterKeyToAction(SDLK_RIGHT, right);
	InputManager::RegisterKeyToAction(SDLK_LEFT, left);
	InputManager::RegisterKeyToAction(SDLK_SPACE, shoot);
	InputManager::RegisterKeyToAction(SDLK_ESCAPE, pause);

	//alternate key binds
	InputManager::RegisterKeyToAction(SDLK_a, left);
	InputManager::RegisterKeyToAction(SDLK_d, right);
}

void Player::ResetPlayer()
{
	m_IsMovingRight = m_IsMovingRight = m_IsShooting = false;
	m_Velocity = 0;
	m_TargetSpeed = 0;
	m_ElapsedTimeSinceShot = 0;
	SetPosition(SVector2D(Graphics::sWindowWidth / 2.f - 64,
		(Graphics::sWindowHeight - (Graphics::sWindowHeight / 5.5f))));
}

void Player::UnBindKeys()
{
	InputManager::ClearKeyBinds();
}

void Player::Update(float deltaTime)
{
	if (m_IsMovingLeft)
	{
		m_TargetSpeed = -kMaxSpeed;
	}
	else if (m_IsMovingRight)
	{
		m_TargetSpeed = kMaxSpeed;
	}
	else
	{
		m_TargetSpeed = 0;
	}
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
				(*iter)->Spawn(kProjectileXOffset, kProjectileYOffset);
				m_ShootSound->Play();
				return;
			}
		}
	}
}

void Player::TimedUpdate(float deltaTime)
{
	m_ElapsedTimeSinceShot += deltaTime;
	
	DetermineVelocity(deltaTime);

	RestrictToScreenBounds();

	if (m_IsShooting && m_ElapsedTimeSinceShot > kFiringCooldown)
	{
		Fire();
		m_ElapsedTimeSinceShot = 0.0f;
	}
	Move(m_Velocity, 0);
}

void Player::RestrictToScreenBounds()
{
	SVector2D *pos = &GetPosition();
	if (pos != nullptr)
	{
		if (pos->x < 0.f)
		{
			m_Velocity = 0;
			SetPosition(0, pos->y);
		}
		else if (pos->x > Graphics::sWindowWidth - Graphics::skSpriteSheetWidth)
		{
			m_Velocity = 0.f;
			SetPosition((float)Graphics::sWindowWidth - (float)Graphics::skSpriteSheetWidth, pos->y);
		}
	}
}

void Player::DetermineVelocity(float deltaTime)
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
}

void Player::Execute(void *params)
{
	KeyBind *action = static_cast<KeyBind*>(params);
	if (action != nullptr)
	{
		if (action->m_KeyState == KeyDown) //KEY DOWN
		{
			switch (action->m_InputAction)
			{
				case Left:
					m_IsMovingLeft = true;
					break;
				case Right:
					m_IsMovingRight = true;
					break;
				case Shoot:
					m_IsShooting = true;
					break;
				default:
					break;
			}
		}
		if (action->m_KeyState == KeyUp) //KEY RELEASED
		{
			switch (action->m_InputAction)
			{
				case Left:
					m_IsMovingLeft = false;
					break;
				case Right:
					m_IsMovingRight = false;
					break;
				case Shoot:
					m_IsShooting = false;
					break;
				case Menu:
					GameManager::Pause();
				default:
					break;
			}
		}
	}
}

void Player::DoCollision(unsigned char collisionType)
{
	if (collisionType & EnemyProjectile)
	{
		--health;
		GameManager::sGame->UpdateHealth();
		if (health <= 0)
		{
			UnBindKeys();
			GameManager::sGame->GameOver();
		}
		ResetPlayer();
	}
}
