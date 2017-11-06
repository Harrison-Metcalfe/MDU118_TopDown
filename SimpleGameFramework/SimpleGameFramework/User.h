#pragma once
#include <iostream>
class User
{
public:
	User();
	virtual ~User();

	void SelectTile();
	void PlaceTile();
	void RemoveTile();
	void SaveLevel();
	void LoadLevel();

public:

	std::string currTile;
	bool removeTiles = false;
	bool isHoldingTile = false;
};

