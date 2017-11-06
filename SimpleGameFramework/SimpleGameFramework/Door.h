#pragma once
#include <iostream>
class Door
{
public:
	Door();
	virtual ~Door();

	void Unlock();
	void DamagePlayer(float damage);

public:
	float damage;
	std::string currSprite;
	bool unlocked = false;
};

