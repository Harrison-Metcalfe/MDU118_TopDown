#pragma once
#include <iostream>
#include "GameObject.h"
#include "GameInput.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	void Move(float moveSpeed);
	void Move_Blink();
	void Attack(float atkStrength);
	void PickUpItem();
	void OpenDoor();
	void Die(float currHealth);

public: 
	float moveSpeed;
	float atkStrength;
	float blinkDist;
	std::string currSprite;

	int keyNum;
	bool hasKey = false;

	float currHealth;
	float maxHealth;

	Vector2i currLocation;
	Vector2i blinkLocation;

};

