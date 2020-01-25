#pragma once
#include "Entity.h"

class Player : Actor
{
public:
	Player();
	~Player();

	void BindKeys();
	void UnBindKeys();

};