#pragma once
#include <iostream>
class Wall
{
public:
	Wall();
	virtual ~Wall();

	void Block();

public:
	Vector2i playerPosition;
	std::string currSprite;
	Vector2i selfPosition;
};

