#include "stdafx.h"
#include "Door.h"


Door::Door()
{
	GameFrameworkInstance.LoadImageResource(
		AppConfigInstance.GetResourcePath("Images/door.png"),
		"Door");

	imageID = "Door";
}


Door::~Door()
{
}

void Door::Unlock()
{
}

void Door::DamagePlayer(float damage)
{
}
