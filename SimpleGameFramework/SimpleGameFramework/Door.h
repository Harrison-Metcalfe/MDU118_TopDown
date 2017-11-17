#pragma once
#include <iostream>
#include "GameObject.h"
class Door : public GameObject
{
public:
	Door();
	virtual ~Door();

	void Unlock();
	void DamagePlayer(float damage);

public:
	float damage;
	bool unlocked = false;
};

