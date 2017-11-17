#pragma once
#include <iostream>
#include "GameObject.h"
class LevelEnd : public GameObject
{
public:
	LevelEnd();
	virtual ~LevelEnd();

	void LevelFinish();

public:
	std::string currSprite;
};

