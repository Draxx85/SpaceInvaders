#pragma once
#include "Actor.h"

class Player : public Actor, Command
{
public:
	Player();
	~Player();

	void BindKeys();
	void UnBindKeys();

	void Update(float deltaTime) override;
	void TimedUpdate(float deltaTime) override;
	void Execute(void* params);

private:
	float const m_kMaxSpeed = 1000;
	float m_CurrentSpeed;
	bool m_IsMoving = true;
	KeyPressState m_KeyState;
	bool m_IsGoingLeft = false;
};