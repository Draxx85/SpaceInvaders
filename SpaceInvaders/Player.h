#pragma once
#include "Actor.h"
#include "MathHelper.h"
#include <stack>
#include "SoundComponent.h"
class Player : public Actor, Command
{
public:
	Player();
	~Player();

	void BindKeys();
	void UnBindKeys();
	void Fire() override;
	void Update(float deltaTime) override;
	void TimedUpdate(float deltaTime) override;
	void Execute(void* params);

private:
	const float kMaxSpeed = 18.f;
	const float kTimeToMaxSpeed = 0.25f;
	const float kSpeedTolerance = 0.25f;
	const float kFiringCooldown = 0.25f;

	SoundComponent *m_ShootSound;

	float m_AccelRatePerSec;
	float m_Velocity;
	float m_TargetSpeed;
	bool m_IsMoving = true;
	KeyPressState m_KeyState;
	bool m_IsGoingLeft = false;
	std::stack<bool> m_KeyPressStack;

	bool m_IsMovingLeft = false;
	bool m_IsMovingRight = false;
	bool m_IsShooting = false;
	float m_ElapsedTimeSinceShot = 0.0f;
	const int kProjectileYOffset = -85;
	
};