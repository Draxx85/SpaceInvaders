#pragma once
#include "Actor.h"

enum Powers
{
	RapidFire,
	Shield,
	LaserBlaster,
	RowSmasher,
};

class Powerup : public Actor
{
public:
	Powerup();
	~Powerup();
};

