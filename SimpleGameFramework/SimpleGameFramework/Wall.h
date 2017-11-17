#pragma once
#include <iostream>
class Wall : public GameObject
{
public:
	Wall();
	virtual ~Wall();

	void Block();

public:
	Vector2i playerPosition;
	Vector2i selfPosition;

protected:
	std::string imageID;
};

