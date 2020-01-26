#pragma once
#include "Actor.h"
#include "MathHelper.h"
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
	const float kMaxSpeed = 65.f;
	const float kTimeToMaxSpeed = 1.05f;
	const float kSpeedTolerance = 3.f;

	float m_AccelRatePerSec;
	float m_Velocity;
	float m_TargetSpeed;
	bool m_IsMoving = true;
	KeyPressState m_KeyState;
	bool m_IsGoingLeft = false;
};