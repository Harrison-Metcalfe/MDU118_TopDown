#pragma once
class Enemy
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
	std::string currSprite;
};

