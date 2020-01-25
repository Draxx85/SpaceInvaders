#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player();
	~Player();

	void BindKeys();
	void UnBindKeys();

};