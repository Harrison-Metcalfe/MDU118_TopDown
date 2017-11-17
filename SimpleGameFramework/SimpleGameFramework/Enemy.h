#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy();

	void Move(float moveSpeed);
	void DamagePlayer(float damage);
	void Die(float currHealth);

public:
	float moveSpeed;
	float damage;
	Vector2i playerPosition;
	
	float currHealth;
	float maxHealth;
};

