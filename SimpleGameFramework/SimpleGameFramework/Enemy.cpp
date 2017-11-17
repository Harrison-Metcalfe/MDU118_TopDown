#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	GameFrameworkInstance.LoadImageResource(
		AppConfigInstance.GetResourcePath("Images/enemy.png"),
		"Enemy");

	imageID = "Enemy";
}


Enemy::~Enemy()
{
}

void Enemy::Move(float moveSpeed)
{
}

void Enemy::DamagePlayer(float damage)
{
}

void Enemy::Die(float currHealth)
{
}
