#pragma once
#include <iostream>
#include "GameObject.h"

class Wall : public GameObject
{
public:
	Wall();
	virtual ~Wall();

	void Block();

public:
	Vector2i playerPosition;
	Vector2i selfPosition;
};

