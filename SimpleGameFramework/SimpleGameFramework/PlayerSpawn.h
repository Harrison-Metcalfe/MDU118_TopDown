#pragma once
#include <iostream>
#include "GameObject.h"
class PlayerSpawn : public GameObject
{
public:
	PlayerSpawn();
	virtual ~PlayerSpawn();

	void SpawnPlayer();

public: 
};

