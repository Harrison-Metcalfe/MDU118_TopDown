#pragma once

#include "GameFramework.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void Draw(Gdiplus::Graphics& canvas);
	void Update(double deltaTime);

public:
	Vector2i location;

protected:
	std::string imageID;
};

