#include "stdafx.h"
#include "PlayerSpawn.h"


PlayerSpawn::PlayerSpawn()
{
	GameFrameworkInstance.LoadImageResource(
		AppConfigInstance.GetResourcePath("Images/spawn.png"),
		"Spawn");

	imageID = "Spawn";
}


PlayerSpawn::~PlayerSpawn()
{
}

void PlayerSpawn::SpawnPlayer()
{
}
