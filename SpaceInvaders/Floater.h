#pragma once
#include "Entity.h"
class Floater :
	public Entity
{
public:
	Floater(const char* msg, SVector2D pos, float lifetime);
	Floater(int value, SVector2D pos, float lifetime);
	void Update(float deltaTime)  override;
	bool m_Active = false;
	void SetupFloater(const char* value, SVector2D pos, float lifetime);
	void UpdateFloater(const char * value, SDL_Color color);
	void CleanFloater();
	void OnSafeClear() override;
	~Floater();
private:
	float m_CountDown;
	bool m_InfiniteLifetime = false;
};

