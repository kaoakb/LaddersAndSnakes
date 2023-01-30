#pragma once
#include "Player.h"
class SpecialAttacks
{
	Player* Attacker;
public:
	SpecialAttacks();
	void Ice();
	void Fire();
	void Poison();
	void Lightning();
	~SpecialAttacks();
};

