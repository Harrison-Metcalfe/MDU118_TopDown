#pragma once
#include <iostream>
class PlayerSpawn
{
public:
	PlayerSpawn();
	virtual ~PlayerSpawn();

	void SpawnPlayer();

public: 
	std::string image;
};

