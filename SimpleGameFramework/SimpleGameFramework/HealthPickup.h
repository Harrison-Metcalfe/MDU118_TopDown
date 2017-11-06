#pragma once
#include <iostream>
class HealthPickup
{
public:
	HealthPickup();
	virtual ~HealthPickup();

	void PickedUp();

public:
	std::string currSprite;
	bool bePickedUp;
};

